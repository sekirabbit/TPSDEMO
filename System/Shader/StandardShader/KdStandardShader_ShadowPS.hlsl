#include "../inc_KdCommon.hlsli"
#include "inc_KdStandardShader.hlsli"

// テクスチャ
Texture2D g_baseTex : register(t0); // ベースカラーテクスチャ
Texture2D g_emissiveTex : register(t1); // エミッシブテクスチャ
Texture2D g_mrTex : register(t2); // メタリック/ラフネステクスチャ
Texture2D g_shadowMapTex : register(t3); //ディザリング用テクスチャ


// サンプラ
SamplerState g_ss : register(s0);

//ベイヤーマトリックスを用意
//bayer行列を用意
static const int bayerMatrix[4][4] =
{
    { 0, 8, 2, 10 },
    { 12, 4, 14, 6 },
    { 3, 11, 1, 9 },
    { 15, 7, 13, 5 }
};

/*
// UnityのBuild-In Shaderでの手法
// RoughnessからSpecularPowerを算出
float RoughnessToSpecPower(float roughness)
{
    float trueRoughness = roughness * roughness; // 学術的に正しいラフネスを求める
    float sq = max(0.0001, trueRoughness * trueRoughness);
    float n = (2.0 / sq) - 2.0;
    // Roughnessが1.0でNdotHがゼロの場合に発生する可能性のあるpow(0,0)のケースを防止
    n = max(n, 0.0001);
    return n;
}
*/

// BlinnPhong NDF
// ・lightDir    … ライトの方向
// ・vCam        … ピクセルからカメラへの方向
// ・normal      … 法線
// ・specPower   … 反射の鋭さ
float BlinnPhong(float3 lightDir, float3 vCam, float3 normal, float specPower)
{
    float3 H = normalize(-lightDir + vCam);
    float NdotH = saturate(dot(normal, H)); // カメラの角度差(0〜1)
    float spec = pow(NdotH, specPower);

    // 正規化Blinn-Phong
    return spec * ((specPower + 2) / (2 * 3.1415926535));
}

//================================
// ピクセルシェーダ
//================================
PSOutput main(VSOutput In) : SV_Target0
{
    // カメラへの方向
    float3 vCam = g_CamPos - In.wPos; // カメラ - ピクセル距離
    float camDist = length(vCam);
    vCam = normalize(vCam);

    // 法線正規化
    float3 wN = 0;
    wN = normalize(In.wN);


    //------------------------------------------
    // 材質色
    //------------------------------------------

    float4 mr = g_mrTex.Sample(g_ss, In.UV);
    // 金属性
    float metallic = mr.b * g_Material.Metallic;
    // 粗さ
    float roughness = mr.g * g_Material.Roughness;
    
     // 材質の色
    float4 baseColor = 0;
    if (g_normalEnable)
    {
        baseColor = g_baseTex.Sample(g_ss, In.UV + wN.xz / 10) * g_Material.BaseColor * In.Color;
    }
    else
    {
        baseColor = g_baseTex.Sample(g_ss, In.UV) * g_Material.BaseColor * In.Color;
    }
    
    // アルファテスト
    if (baseColor.a <= g_AlphaTestThreshold)
        discard;
    //------------------------------------------
    //
    // ライティング
    //
    //------------------------------------------
    // 最終的な色
    float3 color = 0;
    // ライト有効時
    if (g_LightEnable)
    {
		// 材質の拡散色　非金属ほど材質の色になり、金属ほど拡散色は無くなる
        const float3 baseDiffuse = lerp(baseColor.rgb, float3(0, 0, 0), metallic);
		// 材質の反射色　非金属ほど光の色をそのまま反射し、金属ほど材質の色が乗る
        const float3 baseSpecular = lerp(0.04, baseColor.rgb, metallic);

		//------------------
		// 平行光
		//------------------

		// Diffuse(拡散光) 正規化Lambertを使用
		{
			// 光の方向と法線の方向との角度さが光の強さになる
            float lightDiffuse = dot(-g_DL_Dir, wN);
            lightDiffuse = saturate(lightDiffuse); // マイナス値は0にする　0(暗)〜1(明)になる
            if (lightDiffuse < 0.3)
            {
                lightDiffuse = 0.3;
            }
            else if (lightDiffuse < 0.7)
            {
                lightDiffuse = 0.7;
            }
            else
            {
                lightDiffuse = 1.0;
            }
			// 正規化Lambert
            lightDiffuse /= 3.1415926535;

			// 光の色 * 材質の拡散色
            color += (g_DL_Color * lightDiffuse) * baseDiffuse * g_Material.BaseColor.a;
           
        }

		// Specular(反射色) 正規化Blinn-Phong NDFを使用

			// 反射した光の強さを求める

			// ラフネスから、Blinn-Phong用のSpecularPowerを求める
			// Call of Duty : Black OpsやFarCry3でのでの手法を使用
			// specPower = 2^(13*g)　グロス値g = 0〜1で1〜8192のスペキュラ強度を求める
			// 参考：https://hanecci.hatenadiary.org/entry/20130511/p1
        float smoothness = 1.0 - roughness; // ラフネスを逆転させ「滑らか」さにする
        float specPower = pow(2, 13 * smoothness); // 1〜8192

		// UnityのBuild-In Shaderでの手法
		//float spec = RoughnessToSpecPower(roughness);
		{
			// Blinn-Phong NDF
            float spec = BlinnPhong(g_DL_Dir, vCam, wN, specPower);
            if (spec < 1)
            {
                spec = 0;
            }
            //specは１より大きい１、小さい０
            step(1, spec) * 10;
			// 光の色 * 反射光の強さ * 材質の反射色 * 正規化係数
            color += (g_DL_Color * spec) * baseSpecular * g_Material.BaseColor.a;
        }


        //------------------
        // 点光
        //------------------
		{
            for (int pi = 0; pi < g_PL_Num; pi++)
            {

                float3 PL_Dir;

				//点光源に向いたベクトル
                PL_Dir = g_PL[pi].pos - In.wPos;

                float len;
				//点光源の距離
                len = length(PL_Dir);

				//効果半径かどうか
                if (len < g_PL[pi].radius)
                {
                    
					//点光源の方向をnormalize
                    PL_Dir = normalize(PL_Dir);

                    float lightDiffuse;
                    float lightAttenuation;
					//拡散
                    lightDiffuse = saturate(dot(normalize(wN), PL_Dir));
					// 正規化Lambert
                    lightDiffuse /= 3.1415926535;

					//減衰率
                    lightAttenuation = saturate(1.0f - (len / g_PL[pi].radius));

					//ディフューズ減衰
                    lightDiffuse *= lightAttenuation;

                    color += g_PL[pi].color * lightDiffuse * baseDiffuse * g_Material.BaseColor.a;

					//スペキュラ
                    float spec = BlinnPhong(-PL_Dir, vCam, wN, specPower);
                    spec *= lightAttenuation;
                    color += (g_PL[pi].color * spec) * baseSpecular * g_Material.BaseColor.a;
                }
            }
        }
        //------------------
        //スポットライト(2022/9/9)
        //------------------
        {
            for (int si = 0; si < g_SL_Num; si++)
            {
                if (g_SL[si].enable)
                {
                //光源に向いたベクトル
                    float3 toSLDir = g_SL[si].pos - In.wPos;
                //光源の距離
                    float len = length(g_SL[si].dir);
                //効果半径かどうか
                    if (len < g_SL[si].radius)
                    {
                    //光源の方向をnormalize
                        toSLDir = normalize(toSLDir);

                        float rad = acos(saturate(dot(toSLDir, -g_SL[si].dir)));
                    
                        if (rad < g_SL[si].ang)
                        {
                            float angleIn = g_SL[si].ang * 0.5;
                            float side = 1 - ((rad - angleIn) / (g_SL[si].ang - angleIn));
                            float lightDiffuse;
                            float lightAttenuation;
                        //拡散
                            lightDiffuse = saturate(dot(normalize(wN), toSLDir));
                        //光の減衰率
                            lightAttenuation = saturate(1.0f - (len / g_SL[si].radius)) * side;
					    //ディフューズ減衰
                            lightDiffuse *= lightAttenuation;

                            color += g_SL[si].color * baseDiffuse * g_Material.BaseColor.a;

					//スペキュラ
                            float spec = BlinnPhong(-toSLDir, vCam, wN, specPower);
                            spec *= lightAttenuation;
                            color += (g_SL[si].color * spec) * baseSpecular * g_Material.BaseColor.a;
                        }
                    }
                }
            }
        }
        //------------------
        // 環境光
        //------------------
        color += g_AmbientLight * baseColor.rgb * g_Material.BaseColor.a;

        //------------------
        // エミッシブ
        //------------------
        color += g_emissiveTex.Sample(g_ss, In.UV).rgb * g_Material.Emissive * g_Material.BaseColor.a;
        
    }
    // ライト無効時
    else
    {
        // 材質の色をそのまま使用
        color = baseColor.rgb * g_Material.BaseColor.a;
        
    }
  
    //------------------------------------------
    // 出力
    //------------------------------------------
    
    //PSOutput Out;
    //Out.Color = float4(color, baseColor.a);
    //Out.Depth = float4(In.vPos.z, 0, 0, 1);
    PSOutput Out;
    Out.Color = float4(color, baseColor.a);
    Out.Depth = float4(In.vPos.z, 0, 0, 1);
    
    return Out;
    //return Out;


}

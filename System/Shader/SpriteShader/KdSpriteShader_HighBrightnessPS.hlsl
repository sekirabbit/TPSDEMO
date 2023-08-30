#include "inc_KdSpriteShader.hlsli"

// テクスチャ
Texture2D g_inputTex : register(t0);
// サンプラ
SamplerState g_ss : register(s0);


//============================================
// 2D描画 ピクセルシェーダ
//============================================
float4 main(VSOutput In) : SV_Target0
{
    // テクスチャ色取得
    float4 texCol = g_inputTex.Sample(g_ss, In.UV);
    //輝度抽出
    texCol.rgb = max(0, texCol.rgb - 0.4);
    texCol.rgb *= 0.7f;
    
    //アルファテスト
    if (texCol.a < 0.1f) discard;// ピクセル無効

	// テクスチャ色 * 指定色
    return texCol * g_color;

}

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
    //アルファテスト
    if (texCol.a < 0.1f) discard;// ピクセル無効

    //ブラー
    float w, h;
    g_inputTex.GetDimensions(w, h);
    //テクセルサイゼ
    float tw = 1.0f / w;
    float ty = 1.0f / h;
    
    float3 col = g_inputTex.Sample(g_ss, In.UV).rgb; //rgb
    
    for (int i = -g_BlurPower; i < g_BlurPower; i++)
    {
        //テキスチャの色をそのまま描画
        //col += g_inputTex.Sample(g_ss, In.UV).rgb;
        
        //テクスチャの色から右に２ピクセル下に３ピクセルの色が取得
        //col += g_inputTex.Sample(g_ss, In.UV + float2(tw * 2, ty * 3)).rgb;
        
        //下の３ピクセル無効
         //col += g_inputTex.Sample(g_ss, In.UV + float2(tw * 2, ty * 3))*float2(1,0).rgb;
        col += g_inputTex.Sample(g_ss, In.UV + float2(tw * i, ty * i) * g_BlurDir).rgb;
        //ダメージが受けてるイメージをするために赤色を強化する
        col.r *= 1.05f;
    }
    
    col /= (g_BlurPower * 2 + 1); //0を含むから-7～7で15

	// テクスチャ色 * 指定色
    return float4(col, 1);

}

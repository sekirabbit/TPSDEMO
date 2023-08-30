#include "inc_KdSpriteShader.hlsli"

// �e�N�X�`��
Texture2D g_inputTex : register(t0);
// �T���v��
SamplerState g_ss : register(s0);


//============================================
// 2D�`�� �s�N�Z���V�F�[�_
//============================================
float4 main(VSOutput In) : SV_Target0
{
    // �e�N�X�`���F�擾
    float4 texCol = g_inputTex.Sample(g_ss, In.UV);
    //�A���t�@�e�X�g
    if (texCol.a < 0.1f) discard;// �s�N�Z������

    //�u���[
    float w, h;
    g_inputTex.GetDimensions(w, h);
    //�e�N�Z���T�C�[
    float tw = 1.0f / w;
    float ty = 1.0f / h;
    
    float3 col = g_inputTex.Sample(g_ss, In.UV).rgb; //rgb
    
    for (int i = -g_BlurPower; i < g_BlurPower; i++)
    {
        //�e�L�X�`���̐F�����̂܂ܕ`��
        //col += g_inputTex.Sample(g_ss, In.UV).rgb;
        
        //�e�N�X�`���̐F����E�ɂQ�s�N�Z�����ɂR�s�N�Z���̐F���擾
        //col += g_inputTex.Sample(g_ss, In.UV + float2(tw * 2, ty * 3)).rgb;
        
        //���̂R�s�N�Z������
         //col += g_inputTex.Sample(g_ss, In.UV + float2(tw * 2, ty * 3))*float2(1,0).rgb;
        col += g_inputTex.Sample(g_ss, In.UV + float2(tw * i, ty * i) * g_BlurDir).rgb;
        //�_���[�W���󂯂Ă�C���[�W�����邽�߂ɐԐF����������
        col.r *= 1.05f;
    }
    
    col /= (g_BlurPower * 2 + 1); //0���܂ނ���-7�`7��15

	// �e�N�X�`���F * �w��F
    return float4(col, 1);

}

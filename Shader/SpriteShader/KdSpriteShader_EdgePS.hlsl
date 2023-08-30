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
        //�e�N�X�`���̃T�C�Y���擾
    int texW, texH;
    g_inputTex.GetDimensions(texW, texH);
    //g_texel�����Ńs�N�Z���P�ʂ����
    float tw = g_texel / texW;
    float th = g_texel / texH;
    
    //�e�N�X�`���̐F���擾(Z�����擾)
    //       ���������Ă�e�N�X�`��  UV���W
    float z = g_inputTex.Sample(g_ss, In.UV).r;
    
    //�אڂ��Ă���e�N�X�`���̐F
    float z1 = g_inputTex.Sample(g_ss, In.UV + float2(-tw, -th)).r;
    float z2 = g_inputTex.Sample(g_ss, In.UV + float2(0, -th)).r;
    float z3 = g_inputTex.Sample(g_ss, In.UV + float2(tw, -th)).r;
    float z4 = g_inputTex.Sample(g_ss, In.UV + float2(-tw, -0)).r;
    float z5 = g_inputTex.Sample(g_ss, In.UV + float2(tw, 0)).r;
    float z6 = g_inputTex.Sample(g_ss, In.UV + float2(-tw, th)).r;
    float z7 = g_inputTex.Sample(g_ss, In.UV + float2(0, th)).r;
    float z8 = g_inputTex.Sample(g_ss, In.UV + float2(tw, th)).r;
    
    //�������擾
    float v = 0;
    //saturate�֐��͒l���O�`�P�̊Ԃɂ��Ă����i���E�͈͂��K�肷��
    //max(A,B) = A��B���r���đ傫������Ԃ�
    v += saturate(max(0, z1 - z) / g_value);
    v += saturate(max(0, z2 - z) / g_value);
    v += saturate(max(0, z3 - z) / g_value);
    v += saturate(max(0, z4 - z) / g_value);
    v += saturate(max(0, z5 - z) / g_value);
    v += saturate(max(0, z6 - z) / g_value);
    v += saturate(max(0, z7 - z) / g_value);
    v += saturate(max(0, z8 - z) / g_value);
    //pow(A,B) = A��B�悵�Ă���i�ݏ�j
    v = pow(v, g_pow);
    
    return float4(0, 0, 0, v);
}

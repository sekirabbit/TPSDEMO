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
    //�P�x���o
    texCol.rgb = max(0, texCol.rgb - 0.4);
    texCol.rgb *= 0.7f;
    
    //�A���t�@�e�X�g
    if (texCol.a < 0.1f) discard;// �s�N�Z������

	// �e�N�X�`���F * �w��F
    return texCol * g_color;

}

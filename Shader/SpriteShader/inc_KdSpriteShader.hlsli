// �萔�o�b�t�@
cbuffer cbSprite : register(b0)
{
    row_major float4x4  g_mTransform;    // �ϊ��s��
    float4              g_color;
};

cbuffer cbProjection : register(b1)
{
    row_major float4x4  g_mProj;    // �ˉe�ϊ��s��
};
//�u���[��p
cbuffer cbBlur : register(b2)
{
    float2 g_BlurDir;
    int    g_BlurPower;
};

cbuffer cbBright : register(b3)
{
    float2 g_BrightPow;
};

cbuffer cbEdge : register(b4)
{
    int g_EdgeParamEnable;
    float g_texel;
    float g_value;
    float g_pow;
};
// ���_�V�F�[�_�o�͗p
struct VSOutput
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD0;
};
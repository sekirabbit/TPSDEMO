#include "../inc_KdCommon.hlsli"
#include "inc_KdStandardShader.hlsli"

//================================
// ���_�V�F�[�_
//================================
VSOutput main(float4 pos : POSITION, // ���_���W
                float2 uv : TEXCOORD0, // �e�N�X�`��UV���W
                float3 normal : NORMAL, // �@���x�N�g��
                float4 color : COLOR
)
{
    VSOutput Out;
    // �J�����ڐ��ɂ����W�ϊ�(���_���W���ˉe�ϊ����W)
    Out.Pos = mul(pos, g_mW); // ���[�J�����W�n -> ���[���h���W�n�֕ϊ�
    Out.wPos = Out.Pos.xyz;
    Out.Pos = mul(Out.Pos, g_mV); // ���[���h���W�n -> �r���[���W�n�֕ϊ�
    Out.vPos = Out.Pos.xyz;
    Out.Pos = mul(Out.Pos, g_mP); // �r���[���W�n -> �ˉe���W�n�֕ϊ�

    Out.ZCalcTex = mul(pos, g_mW);
    Out.ZCalcTex = mul(Out.ZCalcTex, g_DL_mV); // ���[���h���W�n -> �r���[���W�n�֕ϊ�
   // Out.ZCalcTex = mul(pos, g_DL_mV); // ���[���h���W�n -> �r���[���W�n�֕ϊ�
    Out.lvPos = Out.ZCalcTex.xyz;
    Out.ZCalcTex = mul(Out.ZCalcTex, g_DL_mP); // �r���[���W�n -> �ˉe���W�n�֕ϊ�
    // �@��
    Out.wN = normalize(mul(normal, (float3x3) g_mW));
    // ���_�F
    Out.Color = color;

    //UV���W
    if (g_normalEnable)
    {
        Out.UV = uv * g_UVTiling * 2 + g_UVOffset;
    }
    else
    {
        Out.UV = uv * g_UVTiling + g_UVOffset;
    }
    // �o��
    return Out;
}

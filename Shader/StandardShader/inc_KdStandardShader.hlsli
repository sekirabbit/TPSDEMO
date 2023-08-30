
//===========================================
//
// �萔�o�b�t�@
//  �Q�[���v���O���������玝���Ă���f�[�^
//
//===========================================

// �萔�o�b�t�@(�I�u�W�F�N�g�P�ʍX�V)
cbuffer cbObject : register(b0)
{
    // �I�u�W�F�N�g���
    row_major float4x4 g_mW; // ���[���h�ϊ��s��
    
    // UV����
    float2  g_UVOffset;
    float2  g_UVTiling;
    
    // ���C�g�L��
    int     g_LightEnable;
    // �A���t�@�e�X�g��臒l
    float   g_AlphaTestThreshold;
    //���m�N����
    int g_ColorEnable;
    float g_SetColor_r;
    float g_SetColor_g;
    float g_SetColor_b;
    //�f�B�U�����O
    int g_ditherEnable;
    //�@���}�b�v�L��
    int g_normalEnable;
    //�@��UV����
    float2 g_NormalUVOffset;
    //�������C�g
    int g_LimLightEnable;
    float g_LimLightRate;
    float3 g_LimLightColor;
    //90�x��]�s��
    float4x4 g_mR;

};

//------------------------------
// �萔�o�b�t�@(�}�e���A��)
//------------------------------

// �}�e���A���\����
struct Material
{
    float4 BaseColor;   // �x�[�X�F
    float3 Emissive;    // ���Ȕ����F
    float Metallic;     // �����x
    float Roughness;    // �e��
};

cbuffer cbMaterial : register(b1)
{
    Material g_Material;
    
    //�f�B�]���u�L��
    int g_dissolveEnable;
    //�f�B�]���u�p���[
    float g_dissolvePow;
    //�f�B�]���u�F
    float3 g_dissolveColor;
};

// ���_�V�F�[�_����o�͂���f�[�^
struct VSOutput
{
    float4 Pos : SV_Position;   // �ˉe���W
    float2 UV : TEXCOORD0;      // UV���W
    float3 wN : TEXCOORD1;      // ���[���h�@��
    float4 Color : TEXCOORD2;   // �F
    float3 wPos : TEXCOORD3;    // ���[���h3D���W
    float3 vPos : TEXCOORD4; //�r���[���W
    float4 ZCalcTex : TEXCOORD5;// Z�l�Z�o�p�e�N�X�`��
    float3 lvPos : TEXCOORD6; //���C�g�ڐ��̃r���[���W
};

//�s�N�Z���V�F�[�_�[����o�͂���f�[�^
struct PSOutput
{
    float4 Color : TEXCOORD0;
    float4 Depth : TEXCOORD1;
};

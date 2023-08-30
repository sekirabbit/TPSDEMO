//=====================================================
//
// �S�V�F�[�_����
//
//=====================================================

//------------------------------
// �萔�o�b�t�@(�J����)
//------------------------------
cbuffer cbCamera : register(b7)
{
    // �J�������
    row_major float4x4  g_mV; // �r���[�ϊ��s��
    row_major float4x4  g_mP; // �ˉe�ϊ��s��
    float3              g_CamPos; // �J�������W

	// �t�H�O
    int     g_DistanceFogEnable; // �t�H�O�L��/�����t���O
    float3  g_DistanceFogColor; // �t�H�O�F
    float   g_DistanceFogDensity; // �t�H�O������
};

struct PointLight
{
	float3		color;	//�F
	float		radius;		//���ʔ��a
	float3		pos;		//���̈ʒu
	float					tmp4;
};

struct SpotLight
{
    int enable; //�L����
    float3 pos; //���W
    float3 dir; //����
    float radius; //�����i���ʔ͈́j
    float3 color; //�F
    float ang; //�p�x
};

//------------------------------
// �萔�o�b�t�@(���C�g)
//------------------------------
cbuffer cbLight : register(b8)
{
    // ����
    float3  g_AmbientLight;

    // ���s��
    row_major float4x4 g_DL_mV; // �r���[�ϊ��s��
    row_major float4x4 g_DL_mP; // �ˉe�ϊ��s��
    float3 g_DL_Pos; // ���s�����[���h���W
    float3 g_DL_Dir; // ���̕���
    float3  g_DL_Color;  // ���̐F
    

	// �_����
    row_major float4x4 g_PL_mV; // �r���[�ϊ��s��
    row_major float4x4 g_PL_mP; // �ˉe�ϊ��s��
	PointLight  g_PL[100];	  //�e�|�C���g���C�g�̏��
	int			g_PL_Num;	//�|�C���g���C�g�̐�
    //�X�|�b�g���C�g
    row_major float4x4 g_SL_mV; // �r���[�ϊ��s��
    row_major float4x4 g_SL_mP; // �ˉe�ϊ��s��
    SpotLight   g_SL[100];    //�e�X�|�b�g���C�g�̏��
    int         g_SL_Num;   //�X�|�b�g���C�g�̐�
};

#include "../inc_KdCommon.hlsli"
#include "inc_KdStandardShader.hlsli"

// �e�N�X�`��
Texture2D g_baseTex : register(t0); // �x�[�X�J���[�e�N�X�`��
Texture2D g_emissiveTex : register(t1); // �G�~�b�V�u�e�N�X�`��
Texture2D g_mrTex : register(t2); // ���^���b�N/���t�l�X�e�N�X�`��
Texture2D g_normalTex : register(t3); //�@���}�b�v�p�e�N�X�`��
Texture2D g_dissolveTex : register(t4); //�f�B�U�����O�p�e�N�X�`��
Texture2D g_depthTex : register(t5); //�f�B�U�����O�p�e�N�X�`��


// �T���v��
SamplerState g_ss : register(s0);
SamplerState g_sss : register(s1);
//�x�C���[�}�g���b�N�X��p��
//bayer�s���p��
static const int bayerMatrix[4][4] =
{
    { 0, 8, 2, 10 },
    { 12, 4, 14, 6 },
    { 3, 11, 1, 9 },
    { 15, 7, 13, 5 }
};

/*
// Unity��Build-In Shader�ł̎�@
// Roughness����SpecularPower���Z�o
float RoughnessToSpecPower(float roughness)
{
    float trueRoughness = roughness * roughness; // �w�p�I�ɐ��������t�l�X�����߂�
    float sq = max(0.0001, trueRoughness * trueRoughness);
    float n = (2.0 / sq) - 2.0;
    // Roughness��1.0��NdotH���[���̏ꍇ�ɔ�������\���̂���pow(0,0)�̃P�[�X��h�~
    n = max(n, 0.0001);
    return n;
}
*/

// BlinnPhong NDF
// �ElightDir    �c ���C�g�̕���
// �EvCam        �c �s�N�Z������J�����ւ̕���
// �Enormal      �c �@��
// �EspecPower   �c ���˂̉s��
float BlinnPhong(float3 lightDir, float3 vCam, float3 normal, float specPower)
{
    float3 H = normalize(-lightDir + vCam);
    float NdotH = saturate(dot(normal, H)); // �J�����̊p�x��(0�`1)
    float spec = pow(NdotH, specPower);

    // ���K��Blinn-Phong
    return spec * ((specPower + 2) / (2 * 3.1415926535));
}

//================================
// �s�N�Z���V�F�[�_
//================================
PSOutput main(VSOutput In) : SV_Target0
{

    // �J�����ւ̕��� 
    float3 vCam = g_CamPos - In.wPos; // �J���� - �s�N�Z�����W
    float camDist = length(vCam);
    vCam = normalize(vCam);

    // �@�����K��
    float3 wN = 0;
    if (g_normalEnable)
    {
        //�@���}�b�v����
        //�e�N�X�`���̐F���擾
 //       wN = g_normalTex.Sample(g_ss, In.UV + g_NormalUVOffset);
        // 0-1 �� -1�`1 �ύX����
 //       wN = wN * 2 - 1;
        // �x�N�g�����s��ŕό`
//        wN = mul(wN, (float3x3)g_mR); 
        //��(float3x3)���Ȃ��ꍇ�ŗ΂̔g���́@wN float3�̕ϐ� g_mR��float4x4 �^���Ⴄ�Ōx�񂪏o��
       //���K��
        
        float3 n1 = g_normalTex.Sample(g_ss, In.UV + g_NormalUVOffset);
        float3 n2 = g_normalTex.Sample(g_ss, In.UV - g_NormalUVOffset);
        
        n1 = n1 * 2 - 1;
        n2 = n2 * 2 - 1;
        
        wN = mul(n1 + n2, (float3x3) g_mR);
        
        wN = normalize(wN);

    }
    else
    {
        //�@���}�b�v�Ȃ�(�����ݒ�)
        wN = normalize(In.wN);
    }


    //------------------------------------------
    // �ގ��F
    //------------------------------------------

    float4 mr = g_mrTex.Sample(g_ss, In.UV);
    // ������
    float metallic = mr.b * g_Material.Metallic;
    // �e��
    float roughness = mr.g * g_Material.Roughness;
    
     // �ގ��̐F
    float4 baseColor = 0;
    if (g_normalEnable)
    {
        baseColor = g_baseTex.Sample(g_ss, In.UV + wN.xz / 10) * g_Material.BaseColor * In.Color;
    }
    else
    {
        baseColor = g_baseTex.Sample(g_ss, In.UV) * g_Material.BaseColor * In.Color;
    }
    //�f�B�]���u
    if (g_dissolveEnable)
    {
        float4 dissolveColor = g_dissolveTex.Sample(g_ss, In.UV);
        if (dissolveColor.r < g_dissolvePow)
        {
        //�s�N�Z�����ʂ��o�͂��Ȃ�
            discard; //�i�j���j�߂�l��߂��Ȃ����^�[��
        }
       
        //���ڂ�����������
        if (dissolveColor.r < g_dissolvePow + 0.03f)
        {
            PSOutput Out;
            Out.Color = float4(0.1, 0.6, 0.1, 1);
            //                                            (view)
            //In.vPos.z �[�x�}�b�v�̓J�����Ƃ̋����ł͂Ȃ��r���[���W
            Out.Depth = float4(In.vPos.z, 0, 0, 1);
            //�����̕ϐ���Out�̒��Ɋ܂߂Ă���
            return Out;
        }

    }
    // �A���t�@�e�X�g
    if (baseColor.a <= g_AlphaTestThreshold)
        discard;
    //���m�N����
    if (g_ColorEnable)
    {
        float3 col = (baseColor.r + baseColor.g + baseColor.b) / 3;
        //�Z�s�A��
        col.r *= g_SetColor_r;
        col.g *= g_SetColor_g;
        col.b *= g_SetColor_b;

        baseColor.rgb = col;
    }
    //------------------------------------------
    //
    // ���C�e�B���O
    //
    //------------------------------------------
    // �ŏI�I�ȐF
    float3 color = 0;
    // ���C�g�L����
    if (g_LightEnable)
    {
		// �ގ��̊g�U�F�@������قǍގ��̐F�ɂȂ�A�����قǊg�U�F�͖����Ȃ�
        const float3 baseDiffuse = lerp(baseColor.rgb, float3(0, 0, 0), metallic);
		// �ގ��̔��ːF�@������قǌ��̐F�����̂܂ܔ��˂��A�����قǍގ��̐F�����
        const float3 baseSpecular = lerp(0.04, baseColor.rgb, metallic);

		//------------------
		// ���s��
		//------------------

		// Diffuse(�g�U��) ���K��Lambert���g�p
		{
			// ���̕����Ɩ@���̕����Ƃ̊p�x�������̋����ɂȂ�
            float lightDiffuse = dot(-g_DL_Dir, wN);
            lightDiffuse = saturate(lightDiffuse); // �}�C�i�X�l��0�ɂ���@0(��)�`1(��)�ɂȂ�
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
			// ���K��Lambert
            lightDiffuse /= 3.1415926535;

			// ���̐F * �ގ��̊g�U�F
            color += (g_DL_Color * lightDiffuse) * baseDiffuse * g_Material.BaseColor.a;
        }

		// Specular(���ːF) ���K��Blinn-Phong NDF���g�p

			// ���˂������̋��������߂�

			// ���t�l�X����ABlinn-Phong�p��SpecularPower�����߂�
			// Call of Duty : Black Ops��FarCry3�ł̂ł̎�@���g�p
			// specPower = 2^(13*g)�@�O���X�lg = 0�`1��1�`8192�̃X�y�L�������x�����߂�
			// �Q�l�Fhttps://hanecci.hatenadiary.org/entry/20130511/p1
        float smoothness = 1.0 - roughness; // ���t�l�X���t�]�����u���炩�v���ɂ���
        float specPower = pow(2, 13 * smoothness); // 1�`8192

		// Unity��Build-In Shader�ł̎�@
		//float spec = RoughnessToSpecPower(roughness);
		{
			// Blinn-Phong NDF
            float spec = BlinnPhong(g_DL_Dir, vCam, wN, specPower);
            if (spec < 1)
            {
                spec = 0;
            }
            //spec�͂P���傫���P�A�������O
            step(1, spec) * 10;
			// ���̐F * ���ˌ��̋��� * �ގ��̔��ːF * ���K���W��
            color += (g_DL_Color * spec) * baseSpecular * g_Material.BaseColor.a;
        }


        //------------------
        // �_��
        //------------------
		{
            for (int pi = 0; pi < g_PL_Num; pi++)
            {

                float3 PL_Dir;

				//�_�����Ɍ������x�N�g��
                PL_Dir = g_PL[pi].pos - In.wPos;

                float len;
				//�_�����̋���
                len = length(PL_Dir);

				//���ʔ��a���ǂ���
                if (len < g_PL[pi].radius)
                {
                    
					//�_�����̕�����normalize
                    PL_Dir = normalize(PL_Dir);

                    float lightDiffuse;
                    float lightAttenuation;
					//�g�U
                    lightDiffuse = saturate(dot(normalize(wN), PL_Dir));
					// ���K��Lambert
                    lightDiffuse /= 3.1415926535;

					//������
                    lightAttenuation = saturate(1.0f - (len / g_PL[pi].radius));

					//�f�B�t���[�Y����
                    lightDiffuse *= lightAttenuation;

                    color += g_PL[pi].color * lightDiffuse * baseDiffuse * g_Material.BaseColor.a;

					//�X�y�L����
                    float spec = BlinnPhong(-PL_Dir, vCam, wN, specPower);
                    spec *= lightAttenuation;
                    color += (g_PL[pi].color * spec) * baseSpecular * g_Material.BaseColor.a;
                }
            }
        }
        //------------------
        //�X�|�b�g���C�g(2022/9/9)
        //------------------
        {
            for (int si = 0; si < g_SL_Num; si++)
            {
                if (g_SL[si].enable)
                {
                //�����Ɍ������x�N�g��
                    float3 toSLDir = g_SL[si].pos - In.wPos;
                //�����̋���
                    float len = length(g_SL[si].dir);
                //���ʔ��a���ǂ���
                    if (len < g_SL[si].radius)
                    {
                    //�����̕�����normalize
                        toSLDir = normalize(toSLDir);

                        float rad = acos(saturate(dot(toSLDir, -g_SL[si].dir)));
                    
                        if (rad < g_SL[si].ang)
                        {
                            float angleIn = g_SL[si].ang * 0.5;
                            float side = 1 - ((rad - angleIn) / (g_SL[si].ang - angleIn));
                            float lightDiffuse;
                            float lightAttenuation;
                            //�g�U
                            lightDiffuse = saturate(dot(normalize(wN), toSLDir));
                            //���̌�����
                            lightAttenuation = saturate(1.0f - (len / g_SL[si].radius)) * side;
					        //�f�B�t���[�Y����
                            lightDiffuse *= lightAttenuation;

                            color += g_SL[si].color * baseDiffuse * g_Material.BaseColor.a;

					        //�X�y�L����
                            float spec = BlinnPhong(-toSLDir, vCam, wN, specPower);
                            spec *= lightAttenuation;
                            color += (g_SL[si].color * spec) * baseSpecular * g_Material.BaseColor.a;
                        }
                    }
                }
            }
        }
        //------------------
        // ����
        //------------------
        color += g_AmbientLight * baseColor.rgb * g_Material.BaseColor.a;

        //------------------
        // �G�~�b�V�u
        //------------------
        color += g_emissiveTex.Sample(g_ss, In.UV).rgb * g_Material.Emissive * g_Material.BaseColor.a;
    }
    // ���C�g������
    else
    {
        // �ގ��̐F�����̂܂܎g�p
        color = baseColor.rgb * g_Material.BaseColor.a;
    }

    //------------------------------------------
    // �f�B�U�����O(�f�B�U�����E�A���t�@�f�B�U)
    //------------------------------------------
    {
        if (g_ditherEnable)
        {
        //�X�N���[�����W����
        //�ǂ̃x�C���[�}�g���b�N�X�̐��l���g���̂��Z�o
            int x = fmod(In.Pos.x, 4.0f);
            int y = fmod(In.Pos.y, 4.0f);
        //fmod()...float���m�̗]������߂鉉�Z(�v��%�v�Z)
        //�x�C���[�}�g���b�N�X��臒l���i�[����
            float dither = bayerMatrix[y][x] / 16.0f;
                                        //(0�`1�̊���)
           // float dither2 = bayerMatrix2[y][x] / 5.0f;
        
        //�f�B�U�������J�n����J�����̋���
            float ditherDist = camDist * 0.75f;
        
        //�J������ditherDis�Őݒ肵�������̃s�N�Z�����Ώ�
            float range = (0, camDist - ditherDist);
        //max(a,b)a��b���r���đ傫������Ԃ��֐�

        //�����Z�o
            float rate = 1.0f - min(1.0f, range);
        //min(ab)...a��b���ׂď���������Ԃ��֐�
        
        //0�����ɂȂ�����s�N�Z������u
            clip(dither - 1.0f * rate);
        //clip()...0�����̐�������������N���b�s���O(�`�悵�Ȃ�)
        }
    }

    
    //------------------------------------------
    // �����t�H�O
    //------------------------------------------
    if (g_DistanceFogEnable)
    {
		// �t�H�O 1(�߂�)�`0(����)
        float f = saturate(2.0f / exp(camDist * g_DistanceFogDensity));
        // �K�p
        color.rgb = lerp(g_DistanceFogColor, color.rgb, f);
    }

    //�������C�g
    if (g_LimLightEnable)
    {
         //                      ���f���̃��[���h���W�@�|�@�J�������W
        float limLightPow = dot(normalize(In.wPos - g_CamPos), wN); //wN�͍��̖@��
        limLightPow = 1 - abs(limLightPow); //�}�C�i�X�̉\��������A��Βl����
        color.rgb += float3(g_LimLightColor.r, g_LimLightColor.g, g_LimLightColor.b) * pow(limLightPow, g_LimLightRate); //�Ԃ��J���[�����H���� *pow�ݏ悷��i�����Ȃ�j
    }

    PSOutput Out;
    Out.Color = float4(color, baseColor.a);
    Out.Depth = float4(In.vPos.z, 0, 0, 1);
    return Out;

}

#include "Headers.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
Math::Vector3 GetDot(const Math::Vector3& _rayVec, const Math::Vector3& _normal)
{
	//�i���p�x���Z�o
	Math::Vector3 dot;
	Math::Vector3 toVec;
	toVec = _rayVec;
	//�ǂ̖@���ƈړ������̋t�����x�N�g���œ��ς����߂�
	dot = DirectX::XMVector3Dot(_normal, -toVec);

	return dot;
}



//���f���̂����蔻��֐�
bool ModelIntersects(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec)
{
	float nearestDist = FLT_MAX;	//FLT_MAX==float�^�̍ő�l

	Math::Vector3 hitVPos[3];		//���C�����������|���S���̂R���_���W
	Math::Matrix hitMat;			//���C�����������|���S���̍s��

	for (auto&& node : _model.GetAllNodes())
	{
		//���b�V�����܂܂�Ă��Ȃ��m�[�h�Ȃ��΂�
		if (node.Mesh == nullptr)continue;

		//���̃m�[�h�̃��[���h�s����擾
		Math::Matrix worldMat = node.LocalTransform * _mat;

		//�t�s��
		Math::Matrix inv = worldMat.Invert();

		//�t�s����g���ă��[�J�����W�ɕϊ�
		Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
		Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

		//�g��s����g���Ă��郁�b�V���p�Ƀ��C�̒������v���Ă���
		float rayLen = localDir.Length();

		//�����͕K�������P�ɂ���
		localDir.Normalize();

		//���b�V�����̑S�|���S������
		for (auto&& face : node.Mesh->GetFaces())
		{
			float dist;

			Math::Vector3 vPos[3];//���񃌃C���肷��|���S���̂R���_���W
			vPos[0] = node.Mesh->GetVertexPositions()[face.Idx[0]];
			vPos[1] = node.Mesh->GetVertexPositions()[face.Idx[1]];
			vPos[2] = node.Mesh->GetVertexPositions()[face.Idx[2]];

			bool hit = DirectX::TriangleTests::Intersects(
				localPos,
				localDir,
				vPos[0],//�P���_�ڂ̍��W
				vPos[1],//�Q���_�ڂ̍��W
				vPos[2],//�R���_�ڂ̍��W
				dist	//���C�����������Ƃ���܂ł̋���(�Q�ƌ^)
			);

			if (hit == false)continue;

			//�g�啪�𔽉f
			dist /= rayLen;

			//�����Ƃ��߂��������c��
			if (dist < nearestDist)
			{
				nearestDist = dist;

				//���C�����������|���S���̒��_���W��ۑ�
				hitVPos[0] = vPos[0];
				hitVPos[1] = vPos[1];
				hitVPos[2] = vPos[2];

				//���C�����������|���S���̍s���ۑ�
				hitMat = worldMat;
			}
		}
	}
	if (nearestDist == FLT_MAX)
	{
		return false;
	}
	else {
		_dis = nearestDist;

		//�|���S���̕ӂ�\���x�N�g�������߂�
		Math::Vector3 vec1, vec2;
		vec1 = hitVPos[1] - hitVPos[0];
		vec2 = hitVPos[2] - hitVPos[0];

		//�|���S����ӂɑ΂���O�ρi=���̃|���S���̖@���j
		Math::Vector3 Cross;
		Cross = DirectX::XMVector3Cross(vec1, vec2);

		//�@�������݂̃��f���̌����ɍ��킹�ĉ�]
		_normalVec = DirectX::XMVector3TransformNormal(Cross, hitMat);

		//�@���̐��K��
		_normalVec.Normalize();

		return true;
	}
}



//�����Ŏ󂯎�����x�N�g����
//��(0,0,1)�ɑ΂��Ă̍��E�p�x��߂�l�ŕԂ�
float GetVecAngY(const Math::Vector3& _vec)
{
	Math::Vector3 vec = _vec;
	vec.y = 0;
	vec.Normalize();
	Math::Vector3 dot;
	dot = DirectX::XMVector3Dot(Math::Vector3(0, 0, 1), vec);

	if (dot.x > 1)
	{
		dot.x = 1;
	}
	if (dot.x < -1)
	{
		dot.x = -1;
	}
	float angY;
	angY = DirectX::XMConvertToDegrees(acos(dot.x));
	if (vec.x < 0)
	{
		angY *= -1;
	}




	return angY;
}



//mat�s��ŊǗ����ꂽ�L�����N�^�[��
//_targetAng�x������_plusAng�x��]�����A
//_targetAng�x�܂ł̎c��p�x��߂�l�ŕԂ�
float TurnToAng(Math::Matrix& _mat, const float _targetAng, const float _plusAng)
{
	float currentAng;
	currentAng = GetVecAngY(_mat.Backward());
	//_mat.BackWard() => �s��̑O���x�N�g��
	//�E����W�ƍ�����W�̈Ⴂ����Backward���O����\��
	float lastAng;
	lastAng = _targetAng - currentAng;
	//+180 �` -180�͈̔͂ɂ���
	while (lastAng > 180)
	{
		lastAng -= 360;
	}
	while (lastAng < -180)
	{
		lastAng += 360;
	}
	Math::Matrix tmpMat;
	if (lastAng > _plusAng)//�ڕW�p�x�͉E����
	{
		tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_plusAng));
		lastAng -= _plusAng;
	}
	else
	{
		if (lastAng < -_plusAng)//�ڕW�p�x�͍�����
		{
			tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(-_plusAng));
			lastAng += _plusAng;
		}
		else//�ڕW�p�x�܂�_plusAng�x�ȉ��ł���
		{
			tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(lastAng));
			lastAng = 0;
		}
	}
	_mat = tmpMat * _mat;
	return lastAng;
}



//�ړ��֘A�֐�
Math::Vector3 MoveVec(const float& _ang, const Math::Vector3& _vec)
{
	Math::Vector3 moveVec = {};
	Math::Matrix rotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_ang));
	moveVec += DirectX::XMVector3TransformNormal(_vec, rotMat);
	return moveVec;
}



//���C����֘A�֐�
Math::Vector3 GetLookVec(const float& _angX, const float& _angY)
{
	//�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	Math::Vector3 LookVec;//���Ă����
	Math::Matrix mat;//����������������
	Math::Matrix rotXMat;//X���ŉ�]����̊p�x
	Math::Matrix rotYMat;//Y���ŉ�]����̊p�x

	rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(_angX));
	rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_angY));
	mat = rotXMat * rotYMat;
	//�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	LookVec = XMVector3TransformNormal(Math::Vector3(0, 0, 1), mat);

	return LookVec;
}



//�@���擾
Math::Vector3 GetNormal(const Math::Matrix& _mat)
{
	Math::Vector3 normalVec;
	//															�����͐^�t����
	normalVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, -1), _mat);

	return normalVec;
}


//�L�[�t���[���A�j���[�V����
void AnimeProc(Math::Matrix& _startMat, Math::Matrix& _endMat, const float _animeFrame, Math::Matrix& _mat)
{
	Math::Quaternion startQua;
	Math::Quaternion endQua;
	Math::Quaternion nowQua;

	//�ŏ��ƍŌ�̍s�񂩂�N�H�[�^�j�I�����쐬
	startQua = DirectX::XMQuaternionRotationMatrix(_startMat);
	endQua = DirectX::XMQuaternionRotationMatrix(_endMat);

	//���ԍs������߂�(Slerp:�X���C�h�@| �G�X�@���[�v)
	nowQua = DirectX::XMQuaternionSlerp(startQua, endQua, _animeFrame);;
	_mat = DirectX::XMMatrixRotationQuaternion(nowQua);

	//���ԍ��W�����߂�
	Math::Vector3 startPos;
	Math::Vector3 endPos;
	Math::Vector3 nowPos;

	//�ŏ��ƍŌ�̈ʒu�����߂�(Get translation)
	startPos = _startMat.Translation();
	endPos = _endMat.Translation();

	//���ԍ��W�����߂�(Lerp���[�v)
	nowPos = DirectX::XMVectorLerp(startPos, endPos, _animeFrame);

	//���ԍ��W���s��ɃZ�b�g(Set translation)
	_mat.Translation(nowPos);
}


//�����蔻��i�~����j
bool AttackCheck(Math::Vector3 _attackVec, Math::Vector3 _damageVec, float _hitDis)
{
	//�U�����Ɣ�_���[�W���̋���
	Math::Vector3 attackDis;
	attackDis = _damageVec - _attackVec;

	if (attackDis.Length() <= _hitDis)
	{
		return true;

	}
	return false;
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------


BaseScene::BaseScene()
{
	m_sound = new Sound();
	m_changeSceneWaitTime = ChangeSceneWaitTime;
}

BaseScene::~BaseScene()
{
	delete m_sound;
}

void BaseScene::Frame()
{
	APP.m_console.ClearLog();
	// �Q�[���X�V����
	Update();
	// ���C�g�̃f�[�^����������
	SHADER.m_cb8_Light.Write();
	//��ʂ��N���A
	// �o�b�N�o�b�t�@�N���A
	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 0.0f, 1.0f));//RGBA��0-1�͈̔͂�
	// Z�o�b�t�@�N���A
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	
	SetCamera();
	//�e�N�X�`���ɕ`��
	DynamicDraw();
	// �Q�[���`�揈��
	Draw();
}

void BaseScene::SetCamera()
{
}

void BaseScene::Update()
{
}

void BaseScene::ImGuiUpdate()
{
}

void BaseScene::Draw()
{
}

void BaseScene::DynamicDraw()
{
}


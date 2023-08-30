#include"Headers.h"

Player_rightShoulder::Player_rightShoulder(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_rightShoulder/Player_rightShoulder.gltf");
	m_animeFrame = 0;
	m_addTime = 0.08f;
	m_animeFlg = false;
	m_slashWaitTime = 0;
	m_animeWaitTime = 0;

}

void Player_rightShoulder::Update()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	//���f���̍��W����
	Math::Matrix transMat = DirectX::XMMatrixTranslation(0.4f, 1.8f, -0.2f);
	Math::Matrix rotMat1;
	Math::Matrix rotMat2 = DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(150), 0, 0);
	//���f���̃��[���h���W���X�V����
	
	//��i�K�U���A�j���̐ݒ�
	rotMat1 = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-70));
	m_localMat = rotMat1 * transMat;
	if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash1)
	{
		m_worldMat = m_localMat * playerMan.GetPlayerBody().GetMat();
		m_startMat = m_worldMat;
		m_endMat = rotMat2 * m_startMat;
	}

	if (playerMan.GetPlayer().GetPlayerState() == PlayerState::SlashWait1)
	{
		m_worldMat = rotMat2 * m_localMat * playerMan.GetPlayerBody().GetMat();
	}

	//��i�K�U���A�j���̐ݒ�
	rotMat1 = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-135));
	m_localMat = rotMat1 * transMat;
	if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash2)
	{
		m_worldMat = m_localMat * playerMan.GetPlayerBody().GetMat();
		m_startMat = m_worldMat;
		m_endMat = rotMat2 * m_startMat;
	}

	if (playerMan.GetPlayer().GetPlayerState() == PlayerState::SlashWait2)
	{
		m_worldMat = rotMat2 * m_localMat * playerMan.GetPlayerBody().GetMat();
	}

	if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Stay)
	{
		rotMat1 = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-120));
		m_localMat = rotMat1 * transMat;
		m_worldMat = m_localMat * playerMan.GetPlayerBody().GetMat();
		m_startMat = m_worldMat;
		m_endMat = m_worldMat;
		//�L�[�t���[���A�j���ϐ����X�V����
	}

	//�A�j���t���O�Ǘ�
	if (playerMan.GetPlayer().GetSlashFlg() == true && m_animeFlg == false && m_slashWaitTime <= 0)
	{
		//�A�j���[�V�����n�܂鎞�ɁASE�g�p
		m_animeFrame = 0;
		m_animeFlg = true;
		auto se = m_gameScene->GetSound().GetSlashSEInst();
		se->Play(false);
		//�a���G�t�F�N�g�ǉ�
		//�ŏ��U���̂��߃X�e�[�g�ϊ�
		if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Stay)
		{
			playerMan.GetPlayer().SetPlayerState(PlayerState::Slash1);
		}
	}

	//�A�j���[�V����================================
	if (m_animeFlg == true)
	{
		//if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash1 || playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash2)
		{
			if (m_animeFrame == m_addTime * 3)
			{
				m_gameScene->GetEffectManager().Add(new Explode(m_gameScene));
			}
			//�A�j���I���Ƃ���Ƀv���[���[�̃X�e�[�g�ϊ�
			if (m_animeFrame > 1)
			{
				if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash1)
				{
					playerMan.GetPlayer().SetPlayerState(PlayerState::SlashWait1);
				}
				if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash2)
				{
					playerMan.GetPlayer().SetPlayerState(PlayerState::SlashWait2);
				}
				m_animeFrame = 1;
				m_animeFlg = false;
				playerMan.GetPlayer().SetSlashFlg(false);
				m_slashWaitTime = PlayerSetting::slashWaitTime;
				m_animeWaitTime = PlayerSetting::slashWaitTime;
			}
			//�U�����鎞�ɁA�����I�ɑO�Ɉړ�����
			Math::Vector3 moveVec = GetLookVec(0, playerMan.GetPlayer().GetAng());
			moveVec.y = 0;
			moveVec *= PlayerSetting::slashMovePow;
			playerMan.GetPlayer().AddPos(moveVec);
			playerMan.GetPlayer().MultMat(DirectX::XMMatrixTranslation(0, 0, 0.05f));
			m_animeFrame += m_addTime;
			AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
		}
	}

	//===============================================
	AttackWait();
}

void Player_rightShoulder::AttackWait()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();

	m_slashWaitTime--;
	if (m_slashWaitTime <= 0)
	{
		m_slashWaitTime = 0;
		//�v���[���[�X�e�[�g�̍X�V
		if (playerMan.GetPlayer().GetPlayerState() == PlayerState::SlashWait1)
		{
			playerMan.GetPlayer().SetPlayerState(PlayerState::Slash2);
		}
		if (playerMan.GetPlayer().GetPlayerState() == PlayerState::SlashWait2)
		{
			playerMan.GetPlayer().SetPlayerState(PlayerState::Stay);

		}

	}
}

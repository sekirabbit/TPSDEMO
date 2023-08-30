#include"Headers.h"

BossDoor::BossDoor(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	//�퓬��̌��E�͈͂�ݒ肷�邽�߂ɐ�������Œr�̍��W
	m_swampPos = Math::Vector3(-139.0f, 6.0f, 173.5f);
	//�Q�[����boss�o�����邽�߂ɔ��肷����W
	m_appearPos = BossSetting::makeBossApearPos;
	m_aliveFlg = true;
}

void BossDoor::Update()
{
	if (m_aliveFlg)
	{
		Math::Vector3 targetVec = m_appearPos - m_gameScene->GetPlayerManager().GetPlayer().GetPos();
		//���͈͓̔��ɓ�������boss���o������
		if (targetVec.Length() < 20.0f)
		{
			//Boss���W�ɑ�ʂ̓ŉ��𐶐�����
			for (int i = 0; i < 10; i++)
			{
				//���W��K���ɒ�������
				Math::Vector3 smokePos = Math::Vector3(-191.0f, -7.0f, 178.0f);

				smokePos.y = 5.0f;
				Math::Color color = { 0.2f,0.5f,0.2f,1.0f };
				float size = i * 5.0f;
				m_gameScene->GetEffectManager().Add(new Smoke(smokePos, color, size));
			}

			PlayerManager& playerMan = m_gameScene->GetPlayerManager();

			//���̃��[�V�����֌W�̃J�����̏������W��ݒ肷��
			Math::Vector3 bossPos = BossSetting::beginPos;
			bossPos.y += 17;

			Math::Vector3 camMoveStartPos = m_gameScene->GetCamera().GetCameraPos();
			Math::Vector3 camMoveEndPos = bossPos + Math::Vector3(12.0f, 0, 0);

			m_gameScene->GetCamera().SetCamMovePos(camMoveStartPos, camMoveEndPos);

			Math::Vector3 camMoveStartLock = m_gameScene->GetCamera().GetCameraLock();
			Math::Vector3 camMoveEndLock = bossPos;

			m_gameScene->GetCamera().SetCamMoveLock(camMoveStartLock, camMoveEndLock);

			m_gameScene->GetCamera().SetMoveFlg(true);

			//�m�[�}���G�S�������ł�����
			for (UINT i = 0; i < m_gameScene->GetEnemyManager().GetEnemy().size(); i++)
			{
				m_gameScene->GetEnemyManager().GetEnemy()[i]->HPChange(-500);
			}

			//BOSS���pBGM�ɕύX
			auto bossBgm = m_gameScene->GetSound().GetBossBgmInst();
			auto currentBgm = m_gameScene->GetSound().GetBGMInst();
			if (bossBgm->IsPlay() == false)
			{
				currentBgm->Stop();
				bossBgm->Play(true);
			}
			//���o�̂��ߊ֐����X�V����
			SHADER.m_standardShader.SetDissolvePower(0);

			m_gameScene->GetEnemyManager().SetBossApear(true);
			m_aliveFlg = false;
		}
	}
}

#include"Headers.h"

BossDoor::BossDoor(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	//戦闘場の限界範囲を設定するために生成する毒池の座標
	m_swampPos = Math::Vector3(-139.0f, 6.0f, 173.5f);
	//ゲーム内boss出現するために判定する座標
	m_appearPos = BossSetting::makeBossApearPos;
	m_aliveFlg = true;
}

void BossDoor::Update()
{
	if (m_aliveFlg)
	{
		Math::Vector3 targetVec = m_appearPos - m_gameScene->GetPlayerManager().GetPlayer().GetPos();
		//この範囲内に入ったらbossを出現する
		if (targetVec.Length() < 20.0f)
		{
			//Boss座標に大量の毒煙を生成する
			for (int i = 0; i < 10; i++)
			{
				//座標を適当に調整する
				Math::Vector3 smokePos = Math::Vector3(-191.0f, -7.0f, 178.0f);

				smokePos.y = 5.0f;
				Math::Color color = { 0.2f,0.5f,0.2f,1.0f };
				float size = i * 5.0f;
				m_gameScene->GetEffectManager().Add(new Smoke(smokePos, color, size));
			}

			PlayerManager& playerMan = m_gameScene->GetPlayerManager();

			//そのモーション関係のカメラの初期座標を設定する
			Math::Vector3 bossPos = BossSetting::beginPos;
			bossPos.y += 17;

			Math::Vector3 camMoveStartPos = m_gameScene->GetCamera().GetCameraPos();
			Math::Vector3 camMoveEndPos = bossPos + Math::Vector3(12.0f, 0, 0);

			m_gameScene->GetCamera().SetCamMovePos(camMoveStartPos, camMoveEndPos);

			Math::Vector3 camMoveStartLock = m_gameScene->GetCamera().GetCameraLock();
			Math::Vector3 camMoveEndLock = bossPos;

			m_gameScene->GetCamera().SetCamMoveLock(camMoveStartLock, camMoveEndLock);

			m_gameScene->GetCamera().SetMoveFlg(true);

			//ノーマル敵全員を消滅させる
			for (UINT i = 0; i < m_gameScene->GetEnemyManager().GetEnemy().size(); i++)
			{
				m_gameScene->GetEnemyManager().GetEnemy()[i]->HPChange(-500);
			}

			//BOSS戦専用BGMに変更
			auto bossBgm = m_gameScene->GetSound().GetBossBgmInst();
			auto currentBgm = m_gameScene->GetSound().GetBGMInst();
			if (bossBgm->IsPlay() == false)
			{
				currentBgm->Stop();
				bossBgm->Play(true);
			}
			//演出のため関数を更新する
			SHADER.m_standardShader.SetDissolvePower(0);

			m_gameScene->GetEnemyManager().SetBossApear(true);
			m_aliveFlg = false;
		}
	}
}

#include "Headers.h"

BossVomitAttack::BossVomitAttack()
{
	//出す弾数
	m_outCubeNum = BossSetting::vomitNum;
	//寿命
	m_lastTime = m_outCubeNum * 60;
}

BaseState* BossVomitAttack::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}

	m_lastTime--;
	if (m_lastTime < 0)
	{
		_enemy->SetStateType(EnemyState::Track);
		return new Track();
	}

	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	//VomitAttackの攻撃モード設定
	//敵の照準をプレイヤー現在の位置に移動する
	Math::Vector3 targetVec = playerMan.GetPlayer().GetMat().Translation() - _enemy->GetMat().Translation();
	float enemyAngY = GetVecAngY(targetVec);
	Math::Matrix mat = _enemy->GetMat();
	float ang = TurnToAng(mat, enemyAngY, EnemySetting::focuTurnAng);
	//Y軸回転をm_worldMatに更新
	_enemy->SetMat(mat);

	if (ang == 0)
	{
		//発射時間を設定
		int currentTime = m_lastTime % 60;
		if (currentTime == 0)
		{
			int cubeNum = m_lastTime / 60;
			//弾の初期設定
			Math::Vector3 intPos = _enemy->GetPos() + Math::Vector3{ 0, 2, 0 };

			Math::Vector3 dir = _gameScene->GetPlayerManager().GetPlayer().GetPos() - _enemy->GetPos();
			dir.Normalize();
			float movePow;
			if (_enemy->GetEnemyType() == EnemyType::Boss)
			{
				movePow = BossSetting::vomitSpeed;
				if (_enemy->GetAngry())
				{
					movePow = BossSetting::angryVomitSpeed;
				}
			}
			else
			{
				movePow = EnemySetting::vomitSpeed;
			}
			Math::Matrix mat = DirectX::XMMatrixTranslation(intPos.x, intPos.y, intPos.z);
			
			//se
			auto vomitSE = _gameScene->GetSound().GetVomitAttackSE();
			auto vomitSEInst = vomitSE->CreateInstance(true);
			vomitSEInst->SetVolume(1.0f);
			vomitSEInst->Play();

			_gameScene->GetEffectManager().Add(new Vomit(_gameScene, _enemy, mat, dir, movePow));
		}
	}
	
	return nullptr;
}
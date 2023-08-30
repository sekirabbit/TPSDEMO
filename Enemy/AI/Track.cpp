#include "Headers.h"


BaseState* Track::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}

	PlayerManager& playerMan = _gameScene->GetPlayerManager();
	Math::Vector3 targetVec = playerMan.GetPlayer().GetPos() - _enemy->GetPos();
	float enemyAngY = GetVecAngY(targetVec);
	Math::Matrix mat = _enemy->GetMat();
	float ang = TurnToAng(mat, enemyAngY, EnemySetting::focuTurnAng);
	//Y軸回転をm_worldMatに更新
	_enemy->SetMat(mat);
	if (ang == 0)
	{
		float attackEnableDis;
		float searchingDis;
		EnemyType flg = _enemy->GetEnemyType();
		switch (flg)
		{
		case EnemyType::Normal:
			attackEnableDis = EnemySetting::normalAttackStartDis;
			searchingDis = EnemySetting::searchingRange;
			break;
		case EnemyType::Smoker:
			attackEnableDis = EnemySetting::smokerAttackStartDis;
			searchingDis = EnemySetting::searchingRange;
			break;
		case EnemyType::Boss:
			attackEnableDis = BossSetting::attackStartDis;
			searchingDis = BossSetting::searchingRange;
			break;
		default:
			break;
		}
		if (targetVec.Length() < searchingDis)
		{
			Math::Matrix transMat;
			transMat = DirectX::XMMatrixTranslation(0, 0, EnemySetting::focuSpeed);
			mat = transMat * mat;
			_enemy->SetMat(mat);
			int attackEnable;
			//この範囲内に必ず攻撃する
			if (targetVec.Length() < attackEnableDis)
			{
				_enemy->SetStateType(EnemyState::AttackWait);
				return new AttackWait();
			}
			//範囲外なら可能発動
			else
			{
				attackEnable = rand() % 50;
				if (attackEnable < 1)
				{
					_enemy->SetStateType(EnemyState::AttackWait);
					return new AttackWait();
				}
			}
		}
		else
		{
			if (_enemy->GetEnemyType() != EnemyType::Boss)
			{
				_enemy->SetStateType(EnemyState::Walk);
				return new WalkAround();
			}

		}
	}

	return nullptr;
}
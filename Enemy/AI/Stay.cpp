#include "Headers.h"

BaseState* Stay::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}
	//ステート状態にダメージを受けたらトラック状態に切り替える
	if (_enemy->GetCurrentStateType() == EnemyState::Awake)
	{
		_enemy->SetStateType(EnemyState::Track);
		return new Track();
	}
	EnemyManager& enemyMan = _gameScene->GetEnemyManager();
	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	//攻撃角度を求める(プレイヤーの手前)
	Math::Vector3 targetVec = playerMan.GetPlayer().GetMat().Translation() - _enemy->GetMat().Translation();
	float enemyAngY = GetVecAngY(targetVec);

	float searchingRange;
	if (_enemy->GetEnemyType() == EnemyType::Boss)
	{
		searchingRange = BossSetting::searchingRange;
	}
	else
	{
		searchingRange = EnemySetting::searchingRange;
	}

	//両方の距離は一定の範囲内なら判定する
	if (targetVec.Length() < searchingRange)
	{
		Math::Matrix mat = _enemy->GetMat();
		//目線に入ったらステート変換する
		if (TurnToAng(mat, enemyAngY, EnemySetting::focuTurnAng) <= EnemySetting::searchingAng && TurnToAng(mat, enemyAngY, EnemySetting::focuTurnAng) > -EnemySetting::searchingAng)
		{
			_gameScene->GetEffectManager().Add(new Attention(_enemy));

			_enemy->SetStateType(EnemyState::Track);
			return new Track();
		}
		//近すぎだったらステート変換する
		if (targetVec.Length() < EnemySetting::awakeDis)
		{
			_gameScene->GetEffectManager().Add(new Attention(_enemy));

			_enemy->SetStateType(EnemyState::Track);
			return new Track();
		}
	}

	return nullptr;
}
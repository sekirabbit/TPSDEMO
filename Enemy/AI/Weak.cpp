#include "Headers.h"

Weak::Weak()
{
	m_weakTime = EnemySetting::weakTime;
}

BaseState* Weak::Action(Enemy* _enemy, GameScene* _gameScene)
{
	_enemy->SetStateType(EnemyState::Weak);
	
	m_weakTime--;
	if (m_weakTime < 0)
	{
		if (_enemy->GetEnemyType() == EnemyType::Boss)
		{
			_enemy->SetStateType(EnemyState::Nova);
			return new DrugNova();
		}
		else
		{
			_enemy->SetStateType(EnemyState::Track);
			return new Track();
		}
	}

	if (m_weakTime % 10 == 0)
	{
		if (_enemy->GetEnemyType() == EnemyType::Boss)
		{
			//Boss座標に大量の毒煙を生成する
					//座標を適当に調整する
			Math::Vector3 smokePos = _enemy->GetPos();
			Math::Color color = { 1.0f,1.0f,0.5f,1.0f };
			float size = 10.0f;
			_gameScene->GetEffectManager().Add(new Smoke(smokePos, color, size));
		}
	}
	


	return nullptr;
}
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
			//BossÀ•W‚É‘å—Ê‚Ì“Å‰Œ‚ð¶¬‚·‚é
					//À•W‚ð“K“–‚É’²®‚·‚é
			Math::Vector3 smokePos = _enemy->GetPos();
			Math::Color color = { 1.0f,1.0f,0.5f,1.0f };
			float size = 10.0f;
			_gameScene->GetEffectManager().Add(new Smoke(smokePos, color, size));
		}
	}
	


	return nullptr;
}
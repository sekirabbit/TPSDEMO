#pragma once

class GameScene;

#include"Headers.h"
class EnemyManager
{
public:
	EnemyManager(GameScene* _gameScene);
	~EnemyManager();

	void Draw();
	void Update();

	void AddEnemy(Enemy* _enemy);

	std::vector<Enemy*>& GetEnemy()
	{
		return m_enemy;
	}
	BossEnemy* GetBoss()
	{
		return m_boss;
	}

	void SetBossApear(bool _flg)
	{
		m_bossApearFlg = _flg;
	}
	const bool GetBossApear() const
	{
		return m_bossApearFlg;
	}
	const Math::Vector3& GetBossApearPos()const
	{
		return m_bossApearPos;
	}

	const bool GetClearFlg() const
	{
		return m_clearFlg;
	}
	void SetClearFlg(bool _flg)
	{
		m_clearFlg = _flg;
	}

private:
	GameScene* m_gameScene;
	std::vector<Enemy*>m_enemy;
	BossEnemy* m_boss;
	Math::Vector3 m_bossApearPos;

	bool m_clearFlg;
	bool m_bossApearFlg;

};
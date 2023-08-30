#pragma once

#include"EffectBase.h"
class GameScene;

class HPBar :public EffectBase
{
public:
	HPBar(Enemy* _enemy);
	~HPBar();

	void Draw()override;
	bool Update()override;
private:
	Enemy* m_enemy;

	KdBuffer m_vb;
	KdBuffer m_emptyVb;
	KdTexture* m_enemyHP;
	KdTexture* m_enemyHPEmpty;
};
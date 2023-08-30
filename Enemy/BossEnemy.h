#pragma once

#include"Enemy.h"
class GameScene;

class BossEnemy :public Enemy
{
public:
	BossEnemy(GameScene* _gameScene, const Math::Matrix& _mat);
	~BossEnemy();

	void Update()override;
	void Draw()override;
	void ApearMotion();

	bool CheckEnemy(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec) const override;
private:
	float m_apearMotionTime;
};
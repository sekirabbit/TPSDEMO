#pragma once

class GameScene;

class Heal :public BuffBase
{
public:
	Heal(GameScene* _gameScene, const ObjType& _taker, const float& _healPow);
	bool Update()override;
private:
	float m_healPow;
	float m_addedHP;
};
#pragma once

class WalkAround :public BaseState
{
public:
	WalkAround();
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;


private:
	float m_targetAng;	//目標角度
	int m_lastTime;	//行動継続時間
};
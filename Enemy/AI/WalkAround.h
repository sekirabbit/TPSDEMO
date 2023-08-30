#pragma once

class WalkAround :public BaseState
{
public:
	WalkAround();
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;


private:
	float m_targetAng;	//–Ú•WŠp“x
	int m_lastTime;	//s“®Œp‘±ŠÔ
};
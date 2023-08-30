#pragma once

class Track :public BaseState
{
public:
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;
private:
	int m_lastTime;	//s“®Œp‘±ŠÔ
};
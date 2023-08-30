#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_head :public ObjectBase
{
public:
	Player_head(GameScene* _gameScene);
	void Update()override;
	void Draw()override;
	void BreathMotion(const Math::Matrix& _mat, float& _addFrameTime);
private:
	float m_rgb_g;
	float m_colorChangePow;
};
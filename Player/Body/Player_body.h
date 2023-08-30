#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_body :public ObjectBase
{
public:
	Player_body(GameScene* _gameScene);
	void Update()override;
	void Draw()override;
	void MoveMotion(const Math::Matrix& _mat,float& _addFrameTime);
};
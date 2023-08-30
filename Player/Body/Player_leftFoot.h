#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_leftFoot :public ObjectBase
{
public:
	Player_leftFoot(GameScene* _gameScene);
	void Update()override;

};
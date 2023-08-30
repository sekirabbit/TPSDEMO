#pragma once

#include"ObjectBase.h"
class GameScene;

class Fences :public ObjectBase
{
public:
	Fences(GameScene* _gameScene);
	void Draw()override;
};
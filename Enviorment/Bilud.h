#pragma once

#include"ObjectBase.h"
class GameScene;

class Bilud :public ObjectBase
{
public:
	Bilud(GameScene* _gameScene);
	void Draw()override;
};
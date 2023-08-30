#pragma once

#include"ObjectBase.h"

class GameScene;

class Tree:public ObjectBase
{
public:
	Tree(GameScene* _gameScene, const Math::Matrix& _mat);
	void Update()override;
	void Draw()override;
};
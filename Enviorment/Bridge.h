#pragma once

#include"ObjectBase.h"
class GameScene;

class Bridge :public ObjectBase
{
public:
	Bridge(GameScene* _gameScene);
	void Draw()override;
private:
	KdModel* m_drawModel;
};
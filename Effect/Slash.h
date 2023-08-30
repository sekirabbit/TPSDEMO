#pragma once

#include"EffectBase.h"
class GameScene;

class Slash :public EffectBase
{
public:
	Slash(GameScene* _gameScene, const Math::Vector3& _intPos);
	void Draw()override;
	bool Update()override;
};
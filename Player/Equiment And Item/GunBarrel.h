#pragma once

class GameScene;

class GunBarrel :public ObjectBase
{
public:
	GunBarrel(GameScene* _gameScene);
	void Update()override;
	void Draw()override;
};

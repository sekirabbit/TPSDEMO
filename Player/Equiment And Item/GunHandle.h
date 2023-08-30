#pragma once

class GameScene;

class GunHandle :public ObjectBase
{
public:
	GunHandle(GameScene* _gameScene);
	void Update()override;

};
#pragma once

class GameScene;

class Sword :public ObjectBase
{
public:
	Sword(GameScene* _gameScene);
	void Update()override;
	void Draw()override;
};
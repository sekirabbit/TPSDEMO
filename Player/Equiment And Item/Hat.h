#pragma once

class GameScene;

class Hat :public ObjectBase
{
public:
	Hat(GameScene* _gameScene);
	
	void Update()override;
	void Draw()override;

};
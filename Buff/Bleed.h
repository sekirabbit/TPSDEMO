#pragma once

class GameScene;

class Bleed :public BuffBase
{
public:
	Bleed(GameScene* _gameScene, const ObjType& _taker);
	bool Update()override;

};
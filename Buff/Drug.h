#pragma once

class GameScene;

class Drug :public BuffBase
{
public:
	Drug(GameScene* _gameScene, const ObjType& _taker);
	bool Update()override;

};
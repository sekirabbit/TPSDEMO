#pragma once

class GameScene;
class Enemy;

class BaseState
{
public:
	virtual BaseState* Action(Enemy* _enemy, GameScene* _gameScene) = 0;
	//純粋仮想関数 =>　継承した派生クラス側で
	//その関数をオーバーライドしなければならない
};
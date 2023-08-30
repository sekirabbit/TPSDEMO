#pragma once

#include"ObjectBase.h"
class Enemy;
class GameScene;

class Enemy_body :public ObjectBase
{
public:
	Enemy_body(GameScene* _gameScene,Enemy* _enemy);
	void Update()override;
	void Draw()override;

	KdModel& GetModel()
	{
		return* m_model;
	}
	void SetModel(KdModel* _model)
	{
		m_model = _model;
	}
private:
	GameScene* m_gameScene;
	Enemy* m_enemy;
};
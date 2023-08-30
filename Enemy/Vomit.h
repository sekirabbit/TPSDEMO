#pragma once

#include"EffectBase.h"
class GameScene;
class Enemy;

class Vomit :public EffectBase
{
public:
	Vomit(GameScene* _gameScene, Enemy* _enemy, const Math::Matrix& _mat, const Math::Vector3& _dir, const float& _movePow = 0);
	bool Update()override;
	void Draw()override;
	bool NovaModelUpdate(const float& _size, const float& _alpha);
	void NovaModelDraw();

private:
	GameScene* m_gameScene;
	Enemy* m_enemy;

	KdModel* m_pirpleGalax_cube;
	KdModel* m_galax_cube;
	KdModel* m_pirple_cube;
	KdModel* m_poison_cube;

	Math::Vector2 m_pirpleGalaxuvOffset;
	Math::Vector2 m_galaxuvOffset;
	Math::Vector2 m_poisonuvOffset;

	Math::Vector3 m_startPos;
	Math::Vector3 m_moveVec;

	// ブレンドステート
	ID3D11BlendState* m_blendAlpha;
	ID3D11BlendState* m_blendAdd;

};
#pragma once

class GameClearScene :public BaseScene
{
public:
	GameClearScene();

	void Update()override;
	void Draw()override;


private:
	KdTexture m_mainTex;
	KdTexture* m_clearTex;
	KdTexture* m_returnTex;

	float m_alpha;
	float m_alphaPlusPow = 0.01f;

};
#pragma once

class GameOverScene :public BaseScene
{
public:
	GameOverScene();

	void Update()override;
	void Draw()override;

private:
	KdTexture* m_overTex;
	KdTexture* m_returnTex;

	bool m_changeSceneFlg;

	float m_alpha;
	float m_alphaPlusPow;

};
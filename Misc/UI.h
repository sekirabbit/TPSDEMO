#pragma once

class GameScene;

class UI
{
public:
	UI(GameScene* _gameScene);
	~UI();
	void Draw();
	void Update();

	void HealKeyUpdate();
	void ReloadKeyUpdate();
private:
	GameScene* m_gameScene;

	KdTexture* m_playerHP;
	KdTexture* m_playerHPEmpty; 

	KdTexture* m_enemyHP;
	KdTexture* m_enemyHPEmpty;

	KdTexture* m_bulletIcon;
	KdTexture* m_emptybulletIcon;
	KdTexture* m_reloadKeyIcon;;
	KdTexture* m_mathIcon;

	KdTexture* m_potionIcon;
	KdTexture* m_usePotionKeyIcon;
	KdTexture* m_emptyPotionIcon;

	Math::Matrix m_usePotionKeyMat;;
	float m_usePotionKeyTime;

	KdTexture* m_menuIcon;
	KdTexture* m_questTex;
	KdTexture* m_controlTex;

	float m_playerHPLength;
	float m_playerHPLengthMax; 

	float m_bossHPLength;
	float m_bossHPLengthMax;

	Math::Matrix m_reloadKeyMat;
	float m_reloadKeyTime;

	float m_menuIconAlpha;
	float m_menuIconAddAlpha;


	DirectX::SpriteFont* m_spriteFont;//É|ÉCÉìÉgïœêî
};
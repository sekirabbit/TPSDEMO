#pragma once

class BuffManager;

class GameScene :public BaseScene
{
public:

	// 初期化
	GameScene();
	~GameScene();

	void Frame()override;
	void SetCamera()override;
	// 更新処理
	void Update()override;
	//imgui導入で追加================
	void ImGuiUpdate()override;
	//画面ブラー
	void DynamicDraw()override;
	// 描画処理
	void Draw()override;
	// 終了処理
	void Release();

	void BlurTime();
	void Fade();

	Camera& GetCamera()
	{
		return *m_camera;
	}
	EnviormentManager& GetEnviormentManager()
	{
		return *m_enviormentManager;
	}
	PlayerManager& GetPlayerManager()
	{
		return *m_playerManager;
	}
	EnemyManager& GetEnemyManager()
	{
		return *m_enemyManager;
	}
	ItemManager& GetItemManager()
	{
		return *m_itemManager;
	}
	EffectManager& GetEffectManager()
	{
		return *m_effectManager;
	}
	BuffManager& GetBuffManager()
	{
		return *m_buffManager;
	}

	bool GetMenuOpen()
	{
		return m_openMenuFlg;
	}

private:
	Camera* m_camera;
	EnviormentManager* m_enviormentManager;
	PlayerManager* m_playerManager;
	EnemyManager* m_enemyManager;
	ItemManager* m_itemManager;
	EffectManager* m_effectManager;
	BuffManager* m_buffManager;
	UI* m_UI;

	//全体を含むテクスチャ
	KdTexture m_mainTex;
	//ゲーム画面テクスチャ
	KdTexture m_gameTex;
	//ブラー用テクスチャ
	KdTexture m_blurTex;

	bool m_fadeFlg;
	float m_fadeAlpha;
	int m_blurPower;
	//メニュー関係
	bool m_openMenuFlg;
	float m_bossBGMPower;

	KdTexture* m_normalTex;
	KdTexture* m_dissolveTex;
	KdTexture* m_completeTex;

	bool m_playerCam = true;

};

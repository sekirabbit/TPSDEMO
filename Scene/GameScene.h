#pragma once

class BuffManager;

class GameScene :public BaseScene
{
public:

	// ������
	GameScene();
	~GameScene();

	void Frame()override;
	void SetCamera()override;
	// �X�V����
	void Update()override;
	//imgui�����Œǉ�================
	void ImGuiUpdate()override;
	//��ʃu���[
	void DynamicDraw()override;
	// �`�揈��
	void Draw()override;
	// �I������
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

	//�S�̂��܂ރe�N�X�`��
	KdTexture m_mainTex;
	//�Q�[����ʃe�N�X�`��
	KdTexture m_gameTex;
	//�u���[�p�e�N�X�`��
	KdTexture m_blurTex;

	bool m_fadeFlg;
	float m_fadeAlpha;
	int m_blurPower;
	//���j���[�֌W
	bool m_openMenuFlg;
	float m_bossBGMPower;

	KdTexture* m_normalTex;
	KdTexture* m_dissolveTex;
	KdTexture* m_completeTex;

	bool m_playerCam = true;

};

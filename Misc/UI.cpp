#include"Headers.h"

UI::UI(GameScene* _gameScene)
{
	m_gameScene = _gameScene;

	m_spriteFont = new DirectX::SpriteFont(D3D.GetDev(), L"Data/SpriteFont.dat");

	m_playerHP = RESOURCE.GetTexture("Data/Texture/UI/player_HPBar.png");
	m_playerHPEmpty = RESOURCE.GetTexture("Data/Texture/UI/player_HPBar_empty.png");

	m_enemyHP = RESOURCE.GetTexture("Data/Texture/UI/enemy_HPBar.png");
	m_enemyHPEmpty = RESOURCE.GetTexture("Data/Texture/UI/enemy_HPBar_empty.png");

	m_bulletIcon = RESOURCE.GetTexture("Data/Texture/UI/bullet.png");
	m_emptybulletIcon = RESOURCE.GetTexture("Data/Texture/UI/emptyBullet.png");
	m_mathIcon = RESOURCE.GetTexture("Data/Texture/UI/red_math_icon.png");

	m_potionIcon = RESOURCE.GetTexture("Data/Texture/UI/potion.png");

	m_menuIcon = RESOURCE.GetTexture("Data/Texture/UI/menu_icon.png");
	m_questTex = RESOURCE.GetTexture("Data/Texture/UI/quest.png");
	m_controlTex = RESOURCE.GetTexture("Data/Texture/UI/control.png");
	//�e�N�X�`����maxUV.x
	m_playerHPLengthMax = 178;
	m_playerHPLength = 0;

	m_bossHPLengthMax = 293;
	m_bossHPLength = 0;

	m_menuIconAlpha = 0;
	m_menuIconAddAlpha = 0.01f;

	m_usePotionKeyTime = 60;
	m_reloadKeyTime = 60;
}

UI::~UI()
{
	delete m_menuIcon;
	delete m_spriteFont;
}

void UI::Update()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();

	float currentLength = m_playerHPLength;

	float playerHP = playerMan.GetPlayer().GetHP();
	float playerHPMax = playerMan.GetPlayer().GetHPMax();
	if (playerHP > 0)
	{
		m_playerHPLength = (playerHP / playerHPMax) * m_playerHPLengthMax;
	}
	else
	{
		m_playerHPLength = 0;
	}

	EnemyManager& enemyMan = m_gameScene->GetEnemyManager();

	if (enemyMan.GetBoss()->GetAlive())
	{
		float bossCurrentHP = enemyMan.GetBoss()->GetHP();
		if (bossCurrentHP > 0)
		{
			m_bossHPLength = (bossCurrentHP / BossSetting::maxHp) * m_bossHPLengthMax;
		}
		else
		{
			m_bossHPLength = 0;
		}
	}

	//menuIcon�̓����x
	m_menuIconAlpha += m_menuIconAddAlpha;
	if (m_menuIconAlpha >= 1.0f)
	{
		m_menuIconAddAlpha *= -1;
	}
	if (m_menuIconAlpha <= 0.4f)
	{
		m_menuIconAddAlpha *= -1;
	}

	//�q�[���L�[���ʊ֌W����
	HealKeyUpdate();

	//�����[�h�L�[���ʊ֌W����
	ReloadKeyUpdate();

}

void UI::HealKeyUpdate()
{
	if (m_gameScene->GetPlayerManager().GetPlayer().GetHealWaitTime() == 0)
	{
		if (m_gameScene->GetPlayerManager().GetPlayer().GetHP() < (m_gameScene->GetPlayerManager().GetPlayer().GetHPMax() / 4))
		{

			if (m_usePotionKeyTime > 30)
			{
				m_usePotionKeyMat = DirectX::XMMatrixTranslation(122, -210, 0);
			}
			else
			{
				m_usePotionKeyMat = DirectX::XMMatrixTranslation(122, -200, 0);
			}
			m_usePotionKeyTime--;
			if (m_usePotionKeyTime < 0)
			{
				m_usePotionKeyTime = 60;
			}
		}
		else
		{
			m_usePotionKeyMat = DirectX::XMMatrixTranslation(122, -210, 0);
		}
	}
	else
	{
		m_usePotionKeyMat = DirectX::XMMatrixTranslation(122, -210, 0);
	}
}

void UI::ReloadKeyUpdate()
{
	if (m_gameScene->GetPlayerManager().GetPlayer().GetFireEnableBulletNum() == 0)
	{
		if (m_reloadKeyTime > 30)
		{
			m_reloadKeyMat = DirectX::XMMatrixTranslation(310, -210, 0);
		}
		else
		{
			m_reloadKeyMat = DirectX::XMMatrixTranslation(310, -220, 0);
		}
		m_reloadKeyTime--;
		if (m_reloadKeyTime < 0)
		{
			m_reloadKeyTime = 60;
		}
	}
	else
	{
		m_reloadKeyMat = DirectX::XMMatrixTranslation(310, -220, 0);
	}

}

void UI::Draw()
{
	Math::Matrix tmpMat;
	Math::Matrix scalMat;

	if (m_gameScene->GetMenuOpen() == false)
	{
		SHADER.m_spriteShader.Begin();
	}
	else
	{
		//���j���[�I�[�y����Ԃ̎��ɃQ�[����ʂ������Ȃ邽�ߕʂ̃s�N�Z���V�F�[�_���g��
		SHADER.m_spriteShader.Begin(KdSpriteShader::ShaderTypes::Brightness);
	}
	//playerHPBar��\��
	if (m_playerHPLength > 0)
	{
		tmpMat = DirectX::XMMatrixTranslation(-150, -310, 0);
		scalMat = DirectX::XMMatrixScaling(2, 2, 2);
		tmpMat = scalMat * tmpMat;
		SHADER.m_spriteShader.SetMatrix(tmpMat);
		SHADER.m_spriteShader.DrawTex(m_playerHPEmpty, Math::Rectangle(0, 0, 178, 21), Math::Color(1, 1, 1, 1), { 0,0 });
		SHADER.m_spriteShader.DrawTex(m_playerHP, Math::Rectangle(0, 0, (long)m_playerHPLength, 21), Math::Color(1, 1, 1, 1), { 0,0 });
	}
	EnemyManager& enemyMan = m_gameScene->GetEnemyManager();

	//BossHPBar��\��
	if (m_bossHPLength > 0)
	{
		if (enemyMan.GetBoss()->GetAlive())
		{
			tmpMat = DirectX::XMMatrixTranslation(-450, 300, 0);
			scalMat = DirectX::XMMatrixScaling(3, 1, 1);
			tmpMat = scalMat * tmpMat;
			SHADER.m_spriteShader.SetMatrix(tmpMat);
			SHADER.m_spriteShader.DrawTex(m_enemyHPEmpty, Math::Rectangle(0, 0, 293, 33), Math::Color(1, 1, 1, 1), { 0,0 });
			SHADER.m_spriteShader.DrawTex(m_enemyHP, Math::Rectangle(0, 0, (long)m_bossHPLength, 33), Math::Color(1, 1, 1, 1), { 0,0 });
		}
	}
	int enableBulletNum = m_gameScene->GetPlayerManager().GetPlayer().GetFireEnableBulletNum();
	int usedBulletNum = 2 - enableBulletNum;
	//���[�h�����e��
	for (auto i = 0; i < usedBulletNum; i++)
	{
		//���˂����e�ۂ̃A�C�R����\��
		tmpMat = DirectX::XMMatrixTranslation((float)(322 - i * 32), -310.0f, 0);
		scalMat = DirectX::XMMatrixScaling(3, 3, 3);
		tmpMat = scalMat * tmpMat;
		SHADER.m_spriteShader.SetMatrix(tmpMat);
		SHADER.m_spriteShader.DrawTex(m_emptybulletIcon, Math::Rectangle(0, 0, 11, 27), Math::Color(1, 1, 1, 1), { 0,0 });
	}

	for (auto i = 0; i < enableBulletNum; i++)
	{
		//���ˉ\�Ȓe�ۂ̃A�C�R����\��
		tmpMat = DirectX::XMMatrixTranslation((float)(290 + i * 32), -310.0f, 0);
		scalMat = DirectX::XMMatrixScaling(3, 3, 3);
		tmpMat = scalMat * tmpMat;
		SHADER.m_spriteShader.SetMatrix(tmpMat);
		SHADER.m_spriteShader.DrawTex(m_bulletIcon, Math::Rectangle(0, 0, 11, 27), Math::Color(1, 1, 1, 1), { 0,0 });
	}

	//�����[�h�L�[
	SHADER.m_spriteShader.SetMatrix(m_reloadKeyMat);
	if (m_gameScene->GetPlayerManager().GetPlayer().GetFireEnableBulletNum() == 0)
	{
		m_reloadKeyIcon = RESOURCE.GetTexture("Data/Texture/UI/black_R.png");
	}
	else
	{
		m_reloadKeyIcon = RESOURCE.GetTexture("Data/Texture/UI/white_R.png");
	}
	SHADER.m_spriteShader.DrawTex(m_reloadKeyIcon, Math::Rectangle(0, 0, 24, 24), Math::Color(1, 1, 1, 1), { 0,0 });

	//�\���e�ۂ̃A�C�R����\���i�����Łj
	int allBulletNum = m_gameScene->GetPlayerManager().GetPlayer().GetTakeBulletNum();

	//�~�L��
	scalMat = DirectX::XMMatrixScaling(0.5f, 0.5f, 0.5f);
	tmpMat = DirectX::XMMatrixTranslation(360, -310, 0);
	SHADER.m_spriteShader.SetMatrix(scalMat * tmpMat);
	SHADER.m_spriteShader.DrawTex(m_mathIcon, Math::Rectangle(180, 60, 60, 60), Math::Color(1, 1, 1, 1), { 0,0 });
	//�\���e�ې��i�\�ʁj
	scalMat = DirectX::XMMatrixScaling(0.7f, 0.7f, 0.7f);
	tmpMat = DirectX::XMMatrixTranslation(390, -320, 0);
	SHADER.m_spriteShader.SetMatrix(scalMat * tmpMat);
	int bulletNumTen = allBulletNum / 10 % 10;
	SHADER.m_spriteShader.DrawTex(m_mathIcon, Math::Rectangle(60 * bulletNumTen, 0, 60, 60), Math::Color(1, 1, 1, 1), { 0,0 });

	//�\���e�ې��i��ʁj
	scalMat = DirectX::XMMatrixScaling(0.7f, 0.7f, 0.7f);
	tmpMat = DirectX::XMMatrixTranslation(430, -320, 0);
	SHADER.m_spriteShader.SetMatrix(scalMat * tmpMat);
	int bulletNumUnit = allBulletNum / 1 % 10;
	SHADER.m_spriteShader.DrawTex(m_mathIcon, Math::Rectangle(60 * bulletNumUnit, 0, 60, 60), Math::Color(1, 1, 1, 1), { 0,0 });

	//HP�|�[�V�����̃A�C�R����\��
	//�|�[�V�������g�������ǂ����𔻒f����
	scalMat = DirectX::XMMatrixScaling(3, 3, 3);
	int takeNum = 0;
	if (!m_gameScene->GetPlayerManager().GetPlayer().GetPotion().empty())
	{
		takeNum = m_gameScene->GetPlayerManager().GetPlayer().GetPotion().size();
	}
	//�g����|�[�V�����A�C�R���\��
	for (auto i = 0; i < takeNum; i++)
	{
		tmpMat = DirectX::XMMatrixTranslation((float)(150 - 40 * i), -270, 0);
		SHADER.m_spriteShader.SetMatrix(scalMat* tmpMat);
		SHADER.m_spriteShader.DrawTex(m_potionIcon, Math::Rectangle(0, 0, 16, 17), Math::Color(1, 1, 1, 1), { 0,0 });
	}

	//�A�C�e���g�p�L�[
	float alpha = 1;
	if (m_gameScene->GetPlayerManager().GetPlayer().GetHealWaitTime() > 0)
	{
		alpha = 0.5f;
	}
	if (m_gameScene->GetPlayerManager().GetPlayer().GetHP() < m_gameScene->GetPlayerManager().GetPlayer().GetHPMax() / 4)
	{
		m_usePotionKeyIcon = RESOURCE.GetTexture("Data/Texture/UI/black_E.png");
	}
	else
	{
		m_usePotionKeyIcon = RESOURCE.GetTexture("Data/Texture/UI/white_E.png");
	}
	SHADER.m_spriteShader.SetMatrix(m_usePotionKeyMat);
	SHADER.m_spriteShader.DrawTex(m_usePotionKeyIcon, Math::Rectangle(0, 0, 24, 24), Math::Color(1, 1, 1, alpha), { 0,0 });

	//buff�̃A�C�R����\��
	for (auto i = 0; i < m_gameScene->GetBuffManager().GetBuff().size(); i++)
	{
		tmpMat = DirectX::XMMatrixTranslation(-150 + ((float)i * 40), -270, 0);
		SHADER.m_spriteShader.SetMatrix(tmpMat);
		if (m_gameScene->GetBuffManager().GetBuff()[i]->GetAlive() == true)
		{
			SHADER.m_spriteShader.DrawTex(m_gameScene->GetBuffManager().GetBuff()[i]->GetBuffTex(), Math::Rectangle(0, 0, 40, 40), Math::Color(1, 1, 1, m_gameScene->GetBuffManager().GetBuff()[i]->GetAlpha()), { 0,0 });
		}
	}
	SHADER.m_spriteShader.End();

	SHADER.m_spriteShader.Begin();

	if (m_gameScene->GetMenuOpen())
	{
		//�R���g���[��
		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawTex(m_controlTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, 1));
		SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixTranslation(200, 0, 0));
		SHADER.m_spriteShader.DrawTex(m_questTex, Math::Rectangle(0, 0, 800, 600), Math::Color(1, 1, 1, 1));
	}

	SHADER.m_spriteShader.End();


	//���j���[�A�C�R��
	SHADER.m_spriteShader.Begin();
	tmpMat = DirectX::XMMatrixTranslation(-600, -330, 0);
	SHADER.m_spriteShader.SetMatrix(tmpMat);
	SHADER.m_spriteShader.DrawTex(m_menuIcon, Math::Rectangle(0, 0, 200, 100), Math::Color(1, 1, 1, 1), { 0,0 });

	SHADER.m_spriteShader.End();

}



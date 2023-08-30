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
	//テクスチャのmaxUV.x
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

	//menuIconの透明度
	m_menuIconAlpha += m_menuIconAddAlpha;
	if (m_menuIconAlpha >= 1.0f)
	{
		m_menuIconAddAlpha *= -1;
	}
	if (m_menuIconAlpha <= 0.4f)
	{
		m_menuIconAddAlpha *= -1;
	}

	//ヒールキー効果関係処理
	HealKeyUpdate();

	//リロードキー効果関係処理
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
		//メニューオーペン状態の時にゲーム画面が黒くなるため別のピクセルシェーダを使う
		SHADER.m_spriteShader.Begin(KdSpriteShader::ShaderTypes::Brightness);
	}
	//playerHPBarを表示
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

	//BossHPBarを表示
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
	//ロードした弾丸
	for (auto i = 0; i < usedBulletNum; i++)
	{
		//発射した弾丸のアイコンを表示
		tmpMat = DirectX::XMMatrixTranslation((float)(322 - i * 32), -310.0f, 0);
		scalMat = DirectX::XMMatrixScaling(3, 3, 3);
		tmpMat = scalMat * tmpMat;
		SHADER.m_spriteShader.SetMatrix(tmpMat);
		SHADER.m_spriteShader.DrawTex(m_emptybulletIcon, Math::Rectangle(0, 0, 11, 27), Math::Color(1, 1, 1, 1), { 0,0 });
	}

	for (auto i = 0; i < enableBulletNum; i++)
	{
		//発射可能な弾丸のアイコンを表示
		tmpMat = DirectX::XMMatrixTranslation((float)(290 + i * 32), -310.0f, 0);
		scalMat = DirectX::XMMatrixScaling(3, 3, 3);
		tmpMat = scalMat * tmpMat;
		SHADER.m_spriteShader.SetMatrix(tmpMat);
		SHADER.m_spriteShader.DrawTex(m_bulletIcon, Math::Rectangle(0, 0, 11, 27), Math::Color(1, 1, 1, 1), { 0,0 });
	}

	//リロードキー
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

	//予備弾丸のアイコンを表示（数字で）
	int allBulletNum = m_gameScene->GetPlayerManager().GetPlayer().GetTakeBulletNum();

	//×記号
	scalMat = DirectX::XMMatrixScaling(0.5f, 0.5f, 0.5f);
	tmpMat = DirectX::XMMatrixTranslation(360, -310, 0);
	SHADER.m_spriteShader.SetMatrix(scalMat * tmpMat);
	SHADER.m_spriteShader.DrawTex(m_mathIcon, Math::Rectangle(180, 60, 60, 60), Math::Color(1, 1, 1, 1), { 0,0 });
	//予備弾丸数（十位）
	scalMat = DirectX::XMMatrixScaling(0.7f, 0.7f, 0.7f);
	tmpMat = DirectX::XMMatrixTranslation(390, -320, 0);
	SHADER.m_spriteShader.SetMatrix(scalMat * tmpMat);
	int bulletNumTen = allBulletNum / 10 % 10;
	SHADER.m_spriteShader.DrawTex(m_mathIcon, Math::Rectangle(60 * bulletNumTen, 0, 60, 60), Math::Color(1, 1, 1, 1), { 0,0 });

	//予備弾丸数（一位）
	scalMat = DirectX::XMMatrixScaling(0.7f, 0.7f, 0.7f);
	tmpMat = DirectX::XMMatrixTranslation(430, -320, 0);
	SHADER.m_spriteShader.SetMatrix(scalMat * tmpMat);
	int bulletNumUnit = allBulletNum / 1 % 10;
	SHADER.m_spriteShader.DrawTex(m_mathIcon, Math::Rectangle(60 * bulletNumUnit, 0, 60, 60), Math::Color(1, 1, 1, 1), { 0,0 });

	//HPポーションのアイコンを表示
	//ポーションが使ったかどうかを判断する
	scalMat = DirectX::XMMatrixScaling(3, 3, 3);
	int takeNum = 0;
	if (!m_gameScene->GetPlayerManager().GetPlayer().GetPotion().empty())
	{
		takeNum = m_gameScene->GetPlayerManager().GetPlayer().GetPotion().size();
	}
	//使えるポーションアイコン表示
	for (auto i = 0; i < takeNum; i++)
	{
		tmpMat = DirectX::XMMatrixTranslation((float)(150 - 40 * i), -270, 0);
		SHADER.m_spriteShader.SetMatrix(scalMat* tmpMat);
		SHADER.m_spriteShader.DrawTex(m_potionIcon, Math::Rectangle(0, 0, 16, 17), Math::Color(1, 1, 1, 1), { 0,0 });
	}

	//アイテム使用キー
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

	//buffのアイコンを表示
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
		//コントロール
		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawTex(m_controlTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, 1));
		SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixTranslation(200, 0, 0));
		SHADER.m_spriteShader.DrawTex(m_questTex, Math::Rectangle(0, 0, 800, 600), Math::Color(1, 1, 1, 1));
	}

	SHADER.m_spriteShader.End();


	//メニューアイコン
	SHADER.m_spriteShader.Begin();
	tmpMat = DirectX::XMMatrixTranslation(-600, -330, 0);
	SHADER.m_spriteShader.SetMatrix(tmpMat);
	SHADER.m_spriteShader.DrawTex(m_menuIcon, Math::Rectangle(0, 0, 200, 100), Math::Color(1, 1, 1, 1), { 0,0 });

	SHADER.m_spriteShader.End();

}



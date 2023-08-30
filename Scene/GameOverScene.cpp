#include "Headers.h"

GameOverScene::GameOverScene()
{
	m_overTex = RESOURCE.GetTexture("Data/Texture/Scene/over.png");
	m_returnTex = RESOURCE.GetTexture("Data/Texture/Scene/return.png");

	m_alpha = 0;
	m_alphaPlusPow = 0.01f;
	m_changeSceneFlg = false;
}

void GameOverScene::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (SYSTEM.GetClickKeyFlg() == false)
		{
			SYSTEM.SetClickKeyFlg(true);
			m_changeSceneFlg = true;
			auto se = m_sound->GetStartSEInst();
			se->Play(false);
		}
	}
	else
	{
		SYSTEM.SetClickKeyFlg(false);
	}

	if (m_changeSceneFlg)
	{
		SCENEMANAGER.ChangeScene(new TitleScene());
	}

	m_alpha += m_alphaPlusPow;
	if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_alphaPlusPow = -m_alphaPlusPow;
	}
	if (m_alpha < 0)
	{
		m_alpha = 0;
		m_alphaPlusPow = -m_alphaPlusPow;
	}
}

void GameOverScene::Draw()
{
	SHADER.m_spriteShader.Begin();

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(m_overTex, Math::Rectangle(0, 0, 587, 155), Math::Color{ 1,1,1,1 });

	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixTranslation(0, -180, 0));
	SHADER.m_spriteShader.DrawTex(m_returnTex, Math::Rectangle(0, 0, 878, 88), Math::Color{ 1,1,1,m_alpha });

	SHADER.m_spriteShader.End();
}

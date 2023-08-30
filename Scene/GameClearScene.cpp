#include "Headers.h"

GameClearScene::GameClearScene()
{
	m_mainTex.CreateRenderTarget(ScrW, ScrH);
	m_clearTex = RESOURCE.GetTexture("Data/Texture/Scene/clear.png");
	m_returnTex = RESOURCE.GetTexture("Data/Texture/Scene/return.png");

	m_alpha = 0;
	m_alphaPlusPow = 0.01f;

	m_sound->GetClearSEInst()->Play();
	m_SceneAlpha = 0;

}

void GameClearScene::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (SYSTEM.GetClickKeyFlg() == false)
		{
			SYSTEM.SetClickKeyFlg(true);
			auto se = m_sound->GetStartSEInst();
			se->Play(false);
			SCENEMANAGER.ChangeScene(new TitleScene());
		}
	}
	else
	{
		SYSTEM.SetClickKeyFlg(false);
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

	m_SceneAlpha += 0.01f;
	if (m_SceneAlpha > 1)
	{
		m_SceneAlpha = 1;
	}
}

void GameClearScene::Draw()
{
	D3D.GetDevContext()->ClearRenderTargetView(m_mainTex.GetRTView(), Math::Color(1.0f, 1.0f, 1.0f, 1.0f));//RGBA‚ð0-1‚Ì”ÍˆÍ‚Å

	m_mainTex.SetRenderTarget();
	SHADER.m_spriteShader.Begin();

	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixScaling(0.85f, 0.85f, 0.85f));
	SHADER.m_spriteShader.DrawTex(m_clearTex, Math::Rectangle(0, 0, 986, 143), Math::Color{ 1,1,1,1 });

	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixScaling(0.7f, 0.7f, 1) * DirectX::XMMatrixTranslation(0, -180, 0));
	SHADER.m_spriteShader.DrawTex(m_returnTex, Math::Rectangle(0, 0, 878, 88), Math::Color{ 1,1,1,m_alpha });

	SHADER.m_spriteShader.End();

	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(1.0f, 1.0f, 1.0f, 1.0f));//RGBA‚ð0-1‚Ì”ÍˆÍ‚Å
	D3D.SetBackBuffer();
	SHADER.m_spriteShader.Begin();
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(&m_mainTex, Math::Rectangle(0, 0, 1280, 720), Math::Color(1, 1, 1, m_SceneAlpha));

	SHADER.m_spriteShader.End();





}

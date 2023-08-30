#include"Headers.h"

void GameScene::Update()
{
	//メニュー画面を呼び出す
	if (GetAsyncKeyState('M') & 0x8000)
	{
		if (SYSTEM.GetMenuKeyFlg() == false)
		{
			SYSTEM.SetMenuKeyFlg(true);
			m_openMenuFlg = !m_openMenuFlg;
			m_sound->GetReadSEInst()->Play(false);
		}
	}
	else
	{
		SYSTEM.SetMenuKeyFlg(false);
	}

	//オブジェクトのアップデート
	if (m_playerManager->GetPlayer().GetAlive() == false)
	{
		if (m_playerManager->GetPlayer().DieMotion() == true)
		{
			m_changeSceneWaitTime--;
			if (m_changeSceneWaitTime <= 0)
			{
				SCENEMANAGER.ChangeScene(new GameOverScene());
			}
		}
	}

	m_enviormentManager->Update();


	if (m_openMenuFlg == false)
	{
		m_playerManager->Update();

		m_enemyManager->Update();

		m_itemManager->Update();
	}

	m_camera->Update();

	m_effectManager->Update();

	m_buffManager->Update();

	//UI関係
	m_UI->Update();
	if (m_enemyManager->GetClearFlg() == true)
	{
		m_bossBGMPower -= 0.001f;
		if (m_bossBGMPower <= 0)
		{
			m_bossBGMPower = 0;
		}
		m_sound->GetBossBgmInst()->SetVolume(m_bossBGMPower);
		m_changeSceneWaitTime--;
		if (m_changeSceneWaitTime <= 0)
		{
			SCENEMANAGER.ChangeScene(new GameClearScene());
		}
	}

	if (m_playerManager->GetPlayer().GetAlive() == false)
	{
		m_playerCam = false;
	}
	//画面ブラー時間の設定
	BlurTime();
	Fade();

	//IMGUIを使用不使用
	if (GetAsyncKeyState('9') & 0x8000)
	{
		if (SYSTEM.GetUseImGuiKeyFlg() == false)
		{
			SYSTEM.SetUseImGuiKeyFlg(true);
			m_imguiFlg = !m_imguiFlg;
		}
	}
	else
	{
		SYSTEM.SetUseImGuiKeyFlg(false);
	}
	if (m_imguiFlg)
	{
		ShowCursor(true);
	}
	else
	{
		ShowCursor(false);// マウスでカメラ角度を変換する
	}
}

void GameScene::ImGuiUpdate()
{
	//window1
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiSetCond_Once);

	if (ImGui::Begin("Player"))
	{
		ImGui::Text("[FPS]%d", APP.m_fps);
		ImGui::Text("[BulletNum]%d", m_playerManager->GetPlayer().GetTakeBulletNum());

		ImGui::Text("[Player_Pos]", m_playerManager->GetPlayer().GetMat().Translation());
		Math::Vector3 pp = m_playerManager->GetPlayer().GetMat().Translation();
		ImGui::SliderFloat("POSx", &pp.x, -200, 200);
		ImGui::SliderFloat("POSy", &pp.y, -200, 200);
		ImGui::SliderFloat("POSz", &pp.z, -200, 200);

		m_playerManager->GetPlayer().SetPos(pp);

		if (ImGui::Button("toBossPos")) {
			Math::Vector3 bossPos = Math::Vector3{ -190, 5.0f, 177.8f };
			m_playerManager->GetPlayer().SetPos(bossPos);
		}

		if (ImGui::Button("toBossApearPos")) {
			Math::Vector3 apearPos = Math::Vector3(-151.0f, 7.0f, 171.5f);
			m_playerManager->GetPlayer().SetPos(apearPos);
		}


		if (ImGui::Button("addBulletX99"))
		{
			m_playerManager->GetPlayer().SetTakeBulletNum(99);
		}

		if (ImGui::Button("hitMapEnable"))
		{
			m_playerManager->GetPlayer().SetHitMapFlg(!(m_playerManager->GetPlayer().GetHitMapFlg()));
		}

		if (ImGui::Button("PlayerCamEnable"))
		{
			m_playerCam = !m_playerCam;
		}


	}

	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiSetCond_Once);

	if (ImGui::Begin("Enemy"))
	{
		if (ImGui::Button("KillAllEnemy"))
		{
			for (UINT i = 0; i < m_enemyManager->GetEnemy().size(); i++)
			{
				m_enemyManager->GetEnemy()[i]->HPChange(-9999);
			}
		}
		if (ImGui::Button("KillBoss"))
		{
			m_enemyManager->GetBoss()->HPChange(-9999);
		}
		if (ImGui::Button("BossHPtoHalf"))
		{
			m_enemyManager->GetBoss()->HPChange(-(m_enemyManager->GetBoss()->GetHPMax() / 2));
		}
	}

	ImGui::End();



	ImGui::SetNextWindowPos(ImVec2(0, 200), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiSetCond_Once);

	if (ImGui::Begin("System"))
	{
		//平行光の方向
		ImGui::Text("parallel light");
		Math::Vector3 dl = SHADER.m_cb8_Light.Work().DL_Dir;
		ImGui::SliderFloat("DLx", &dl.x, -1, 1);
		ImGui::SliderFloat("DLy", &dl.y, -1, 1);
		ImGui::SliderFloat("DLz", &dl.z, -1, 1);

		SHADER.m_cb8_Light.Work().DL_Dir = dl;

		SHADER.m_cb8_Light.Write();

		if (ImGui::Button("FrogEnable")) {
			if (SHADER.m_cb7_Camera.Work().DistanceFogEnable == 1)
			{
				SHADER.m_cb7_Camera.Work().DistanceFogEnable = false;
			}
			else
			{
				SHADER.m_cb7_Camera.Work().DistanceFogEnable = true;
			}
		}

		if (ImGui::Button("ToTitle"))
		{
			SCENEMANAGER.ChangeScene(new TitleScene());
		}

		if (ImGui::Button("HitMapDraw"))
		{
			m_enviormentManager->SetHitMapDrawEnable(!m_enviormentManager->GetHitMapDrawEnable());
		}

		if (ImGui::Button("AddTree"))
		{
			Tree* tree = new Tree(this, m_playerManager->GetPlayer().GetMat());
			m_enviormentManager->AddTree(tree);
		}

	}

	ImGui::End();

}

void GameScene::DynamicDraw()
{
	if (m_playerCam == true)
	{
		SetCamera();
	}
	D3D.GetDevContext()->ClearRenderTargetView(m_gameTex.GetRTView(), Math::Color(0.5f, 0.6f, 0.5f, 1.0f));//RGBAを0-1の範囲で
	//レンダーターゲットを切り替える
	m_gameTex.SetRenderTarget();
	SHADER.m_standardShader.SetToDevice();
	m_enviormentManager->Draw();

	m_playerManager->Draw();
	m_enemyManager->Draw();
	m_itemManager->Draw();

	SHADER.m_effectShader.SetToDevice();
	m_effectManager->Draw();

}

void GameScene::Draw()
{
	//UI設定から初期設定に戻す
	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());

	//============================
	//ブラー
	//============================
	//作業用テクスチャを作成
	KdTexture workTex;
	workTex.CreateRenderTarget(ScrW, ScrH);
	//横にぼかす
	workTex.SetRenderTarget();
	//ブラータイムによって、ブラーの強さを減少していく
	m_blurPower = (int)(m_blurTime / (PlayerSetting::blurTime / 7));
	SHADER.m_spriteShader.SetBlurPower(m_blurPower);
	SHADER.m_spriteShader.SetBlurDir({ 1,0 });
	SHADER.m_spriteShader.Begin(KdSpriteShader::ShaderTypes::Blur);

	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
	SHADER.m_spriteShader.DrawTex(&m_gameTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, 1));

	SHADER.m_spriteShader.End();

	//縦にぼかす
	m_blurTex.SetRenderTarget();
	SHADER.m_spriteShader.SetBlurDir({ 0,1 });
	SHADER.m_spriteShader.Begin(KdSpriteShader::ShaderTypes::Blur);

	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
	SHADER.m_spriteShader.DrawTex(&workTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, 1));

	SHADER.m_spriteShader.End();

	m_mainTex.SetRenderTarget();

	if (m_blurFlg == true)
	{
		SHADER.m_spriteShader.Begin();
		SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
		SHADER.m_spriteShader.DrawTex(&m_blurTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, 1));
		SHADER.m_spriteShader.End();
	}
	else
	{
		if (m_openMenuFlg == true)
		{
			//メニューを開いてる時にゲーム画面のテクスチャを黒くする
			SHADER.m_spriteShader.Begin(KdSpriteShader::ShaderTypes::Brightness);
		}
		else
		{
			SHADER.m_spriteShader.Begin();
		}
		SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
		SHADER.m_spriteShader.DrawTex(&m_gameTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, 1));
		SHADER.m_spriteShader.End();
	}

	//UI（アイコンなど）を表示
	m_UI->Draw();

	//レンダーターゲットをバックバッファに変更
	D3D.SetBackBuffer();
	SHADER.m_spriteShader.Begin(); 
	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
	if (m_fadeFlg)
	{
		SHADER.m_spriteShader.DrawTex(&m_mainTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, m_fadeAlpha));
	}
	else
	{
		SHADER.m_spriteShader.DrawTex(&m_mainTex, Math::Rectangle(0, 0, ScrW, ScrH), Math::Color(1, 1, 1, m_changeSceneWaitTime / ChangeSceneWaitTime));
	}
	SHADER.m_spriteShader.End();



	workTex.Release();
}

void GameScene::Frame()
{
	APP.m_console.ClearLog();
	// ゲーム更新処理
	Update();
	// ライトのデータを書き込む
	SHADER.m_cb8_Light.Write();
	//画面をクリア(最初の青い画面)
	// バックバッファクリア
	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 0.0f, 1.0f));//RGBAを0-1の範囲で
	// Zバッファクリア
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	//テクスチャに描画
	DynamicDraw();
	// ゲーム描画処理
	Draw();

}

GameScene::GameScene()
{
	// 平行ライト設定
	SHADER.m_cb8_Light.Work().DL_Dir = { -1,1,1 };
	SHADER.m_cb8_Light.Work().DL_Dir.Normalize();
	SHADER.m_cb8_Light.Work().DL_Color = { 1.5f,1.5f,1.5f };

	m_camera = new Camera(this);
	m_enviormentManager = new EnviormentManager(this);
	m_playerManager = new PlayerManager(this);
	m_enemyManager = new EnemyManager(this);
	m_itemManager = new ItemManager(this);
	m_effectManager = new EffectManager(this);
	m_buffManager = new BuffManager(this);

	m_UI = new UI(this);
	m_sound = new Sound();
	m_fadeFlg = true;
	m_fadeAlpha = 0;
	m_changeSceneWaitTime =	180;
	//全体を含むテクスチャ
	m_mainTex.CreateRenderTarget(ScrW, ScrH);
	//描画用テクスチャ
	m_gameTex.CreateRenderTarget(ScrW, ScrH);
	//ブラー用
	m_blurFlg = false;
	m_blurTex.CreateRenderTarget(ScrW, ScrH);
	//Blurの強さ
	m_blurPower = 0;

	//メニュー関係
	m_openMenuFlg = false;


	//モノクロ化
	SHADER.m_standardShader.SetColorEnable(false);
	//ゲームクリア用テクスチャ
	m_completeTex = RESOURCE.GetTexture("Data/Texture/UI/clean.png");
	//法線マップロード
	m_normalTex = RESOURCE.GetTexture("Data/Texture/water_normal.jpg");
	D3D.GetDevContext()->PSSetShaderResources(3, 1, m_normalTex->GetSRViewAddress());
	Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90));
	SHADER.m_standardShader.SetNormalMat(rotMat);
	//ディゾルブ
	m_dissolveTex = RESOURCE.GetTexture("Data/Texture/dissolve.png");
	D3D.GetDevContext()->PSSetShaderResources(4, 1, m_dissolveTex->GetSRViewAddress());
	//距離フォグ（霧）の設定
	//シェーダプログラムで実装
	SHADER.m_cb7_Camera.Work().DistanceFogEnable = 1;//フォグを有効化
	SHADER.m_cb7_Camera.Work().DistanceFogColor = { 0.5f,0.6f,0.5f };//フォグの色（RGB）
	SHADER.m_cb7_Camera.Work().DistanceFogDensity = 0.04f;//フォグの強さ

	//BGM
	if (m_sound->GetBGMInst()->IsPlay() == false)
	{
		m_sound->GetBGMInst()->SetPitch(-0.2f);
		m_sound->GetBGMInst()->SetVolume(0.2f);
		m_sound->GetBGMInst()->Play(true);
	}

	
	m_bossBGMPower = 0.3f;
	m_sound->GetBossBgmInst()->SetVolume(m_bossBGMPower);

}

GameScene::~GameScene()
{
	m_sound->GetBossBgmInst()->Stop();
	m_sound->GetBGMInst()->Stop();

	m_enviormentManager->~EnviormentManager();
}

void GameScene::Release()
{
	delete m_camera;
	delete m_enviormentManager;
	delete m_playerManager;
	delete m_enemyManager;
	delete m_itemManager;
	delete m_effectManager;
	delete m_buffManager;
	delete m_UI;
	delete m_sound;

}

void GameScene::SetCamera()
{
	//カメラ
	//カメラのビュー変換行列
	SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH(m_camera->GetCameraPos(), m_camera->GetCameraLock(), m_camera->GetCameraHead());
	SHADER.m_cb7_Camera.Work().CamPos = SHADER.m_cb7_Camera.Work().mV.Invert().Translation();
	//カメラの射影行列
	SHADER.m_cb7_Camera.Work().mP = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90), (float)ScrW / (float)ScrH, 0.01f, 2000.0f);
	SHADER.m_cb7_Camera.Write();

}

void GameScene::BlurTime()
{
	m_blurTime--;
	if (m_blurTime <= 1)
	{
		m_blurTime = 1;
		m_blurFlg = false;
	}
	else
	{
		m_blurFlg = true;
	}
}

void GameScene::Fade()
{
	m_fadeAlpha += 0.01f;
	if (m_fadeAlpha > 1)
	{
		m_fadeAlpha = 1;
		m_fadeFlg = false;
	}
}

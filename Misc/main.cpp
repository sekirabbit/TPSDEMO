#include"Headers.h"

//===================================================================
// メイン
//===================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	// メモリリークを知らせる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// COM初期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	// mbstowcs_s関数で日本語対応にするために呼ぶ
	setlocale(LC_ALL, "japanese");

	//===================================================================
	// 実行
	//===================================================================
	APP.Execute();

	// COM解放
	CoUninitialize();

	return 0;
}


// アプリケーション初期設定
bool Application::Init(int w, int h)
{

	//===================================================================
	// ウィンドウ作成
	//===================================================================
	if (m_window.Create(w, h, "Zombie × Hunter", "Window") == false) {
		MessageBoxA(nullptr, "ウィンドウ作成に失敗", "エラー", MB_OK);
		return false;
	}

	//===================================================================
	// フルスクリーン確認
	//===================================================================
	//trueなら完全フルスクリーンにする
	bool bFullScreen = false;
	if (MessageBoxA(m_window.GetWndHandle(), "フルスクリーンにしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}


	//===================================================================
	// Direct3D初期化
	//===================================================================

	// デバイスのデバッグモードを有効にする
	bool deviceDebugMode = false;
#ifdef _DEBUG
	deviceDebugMode = true;
#endif

	// Direct3D初期化
	std::string errorMsg;
	if (D3D.Init(m_window.GetWndHandle(), w, h, deviceDebugMode, errorMsg) == false) {
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "Direct3D初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	// フルスクリーン設定
	if (bFullScreen) {
		D3D.GetSwapChain()->SetFullscreenState(TRUE, 0);
	}

	// シェーダー初期化
	SHADER.Init();

	//===================================================================
	// サウンド初期化
	//===================================================================
	if (AUDIO.Init() == false)
	{
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "サウンド初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	//===================================================================
	// imgui初期設定
	//===================================================================
	//imgui導入で追加==============================================
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();
	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(m_window.GetWndHandle());
	ImGui_ImplDX11_Init(D3D.GetDev(), D3D.GetDevContext());

	{
		// 日本語対応
#include "imgui/ja_glyph_ranges.h"
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 13.0f, &config, glyphRangesJapanese);
	}

	return true;
	//===================================================================================================================
}


// アプリケーション終了
void Application::Release()
{
	//imgui導入で追加==================
	// imgui解放
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	//==================================
	// シェーダ解放
	SHADER.Release();

	// Direct3D解放
	D3D.Release();

	// XAudio2解放
	AUDIO.Release();

	// ウィンドウ削除
	m_window.Release();

}

// アプリケーション実行
void Application::Execute()
{
	//===================================================================
	// 初期設定(ウィンドウ作成、Direct3D初期化など)
	//===================================================================
	if (APP.Init(ScrW, ScrH) == false) {
		return;
	}

	//===================================================================
	// ゲームループ
	//===================================================================

	// 時間
	DWORD baseTime = timeGetTime();
	int count = 0;
	//						最初に表示するスクリーン
	SCENEMANAGER.ChangeScene(new TitleScene());

	// ループ
	while (1)
	{

		// 処理開始時間Get
		DWORD st = timeGetTime();

		// ゲーム終了指定があるときはループ終了
		if (m_endFlag)
		{
			break;
		}

		//=========================================
		//
		// ウィンドウ関係の処理
		//
		//=========================================

		// ウィンドウのメッセージを処理する
		m_window.ProcessMessage();

		// ウィンドウが破棄されてるならループ終了
		if (m_window.IsCreated() == false)
		{
			break;
		}

		//=========================================
		//
		// オーディオ処理
		//
		//=========================================
		AUDIO.Update();

		//=========================================
		//
		// ゲーム処理
		//
		//=========================================
		SCENEMANAGER.DoScene();
		//タイトル画面でEnterを押すと
		//ゲーム画面に切り替わるようにする

		//FPS表示（タイトルバー）
		std::string titleBar = "Zombie × Hunte	  FPS:" + std::to_string(m_fps);
		SetWindowTextA(APP.m_window.GetWndHandle(), titleBar.c_str());
		D3D.GetSwapChain()->Present(0, 0);

		//=========================================
		//
		// フレームレート制御
		//
		//=========================================
		// 処理終了時間Get
		DWORD et = timeGetTime();
		// Fps制御
		DWORD ms = 1000 / m_maxFps;
		if (et - st < ms)
		{
			Sleep(ms - (et - st));	// 速すぎたら待つ
		}

		// FPS計測
		count++;
		if (st - baseTime >= 500)
		{
			m_fps = (count * 1000) / (st - baseTime);
			baseTime = st;
			count = 0;
		}

	}


	//===================================================================
	// アプリケーション解放
	//===================================================================
	Release();
}
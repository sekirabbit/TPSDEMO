#pragma once

class SceneManager
{
public:

	~SceneManager();

	void DoScene();
	void ChangeScene(BaseScene* _nextScene);

	//シングルトン
	//ひとつ　down
	//自分で

	//実体を宣言して返す (関数名)
	static SceneManager& GetInstance()
	{
		static SceneManager sceneManager;

		return sceneManager;
	}

private:
	//シングルトンの特徴とは
	//コンストラクタの位置はprivateにある
	SceneManager()
	{
	}

	//継承関係の中に一番年上のクラスで(BaseScene=基底クラス)
	BaseScene* m_currentScene = nullptr;//現在実行中のシーン
	BaseScene* m_nextScene = nullptr;//つきに実行したいのシーン

	//State(ステート)パターン
	//デザインパターンのひとつで
	//ある状態を表すクラスを個々に作り
	//今現在の状態を表すクラスを持つようにする

};

//マクロ(事前に設定完了の命令)を作成
#define SCENEMANAGER SceneManager::GetInstance()

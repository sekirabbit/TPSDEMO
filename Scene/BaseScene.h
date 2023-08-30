#pragma once
class Sound;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Frame();
	virtual void SetCamera();
	virtual void Update();
	virtual void ImGuiUpdate();
	virtual void Draw();
	virtual void DynamicDraw();

	Sound& GetSound()
	{
		return *m_sound;
	}
	bool GetImGuiFlg()
	{
		return m_imguiFlg;
	}

	void SetImGuiFlg(bool _flg)
	{
		m_imguiFlg = _flg;
	}

	void SetBlurFlg(bool _flg)
	{
		m_blurFlg = _flg;
	}

	void SetBlurTime(float _time)
	{
		m_blurTime = _time;
	}

protected:
	bool m_imguiFlg = false;

	bool m_blurFlg = false;
	float m_blurTime = 0;

	float m_changeSceneWaitTime;
	float m_SceneAlpha;

	Sound* m_sound;


};
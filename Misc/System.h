#pragma once
class System
{
public:
	static System& GetInstance()
	{
		static System system;

		return system;
	}

	bool GetClickKeyFlg()const //4bit->16bit
	{
		return m_clickFlg;
	}
	void SetClickKeyFlg(bool _flg)
	{
		m_clickFlg = _flg;
	}

	bool GetUseImGuiKeyFlg()const
	{
		return m_useImGuiKeyFlg;
	}
	void SetUseImGuiKeyFlg(bool _flg)
	{
		m_useImGuiKeyFlg = _flg;
	}

	bool GetMenuKeyFlg()const
	{
		return m_menuFlg;
	}
	void SetMenuKeyFlg(bool _flg)
	{
		m_menuFlg = _flg;
	}

	bool GetFocusKeyFlg()const
	{
		return m_focusKeyFlg;
	}
	void SetFocusKeyFlg(bool _flg)
	{
		m_focusKeyFlg = _flg;
	}

	bool GetFocusCancelKeyFlg()const
	{
		return m_focusCancelFlg;
	}
	void SetFocusCancelKeyFlg(bool _flg)
	{
		m_focusCancelFlg = _flg;
	}

	bool GetSlashKeyFlg()const
	{
		return m_slashFlg;
	}
	void SetSlashKeyFlg(bool _flg)
	{
		m_slashFlg = _flg;
	}

	bool GetFireKeyFlg()const
	{
		return m_fireFlg;
	}
	void SetFireKeyFlg(bool _flg)
	{
		m_fireFlg = _flg;
	}
	
	bool GetReloadKeyFlg()const
	{
		return m_reloadFlg;
	}
	void SetReloadKeyFlg(bool _flg)
	{
		m_reloadFlg = _flg;
	}

	bool GetHealKeyFlg()const
	{
		return m_healFlg;
	}
	void SetHealKeyFlg(bool _flg)
	{
		m_healFlg = _flg;
	}

private:
	//シングルトン
	System()
	{
	}

	bool m_clickFlg = false;
	bool m_useImGuiKeyFlg = false;
	bool m_focusKeyFlg = false;
	bool m_focusFlg = false;
	bool m_focusCancelFlg = false;
	bool m_menuFlg = false;
	bool m_slashFlg = false;
	bool m_fireFlg = false;
	bool m_reloadFlg = false;
	bool m_healFlg = false;
};
//シングルトン
#define SYSTEM System::GetInstance()
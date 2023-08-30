#pragma once

#include"ObjectBase.h"
class GameScene;
class Heal;

class Player :public ObjectBase
{
public:
	Player(GameScene* _gameScene);
	void AddPos(const Math::Vector3& _pos)override;

	void Update(float _camAngY);
	void Control(const float& _ang);
	void KnockBack();
	void SetKnockBack(bool _flg, const Math::Vector3& _backVec, const float& _backPow);
	
	void Slash();
	void Shot();
	void Reload();
	void DrinkPotion();
	void HPChange(const float& _changePow);
	bool DieMotion();
	bool CheckPlayer(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec) const;


	const float& GetHP()const
	{
		return m_hp;
	}
	const float& GetHPMax()const
	{
		return m_hpMax;
	}
	
	const bool& GetCamLock()const
	{
		return m_camLockFlg;
	}
	void SetCamLock(bool& _flg)
	{
		m_camLockFlg = _flg;
	}

	void SetAng(const float& _ang)
	{
		m_ang = _ang;
	}
	void AddAng(const float& _ang)
	{
		m_ang += _ang;
	}
	const bool& GetAlive()const
	{
		return m_aliveFlg;
	}

	const bool& GetDieMotionFlg()const
	{
		return m_dieMotionFlg;
	}
	void SetDieMotionFlg(bool _flg)
	{
		m_dieMotionFlg = _flg;
	}

	const bool& GetMoveFlg()const
	{
		return m_moveFlg;
	}

	const bool& GetHitMapFlg()const
	{
		return m_hitMapFlg;
	}
	void SetHitMapFlg(bool _flg)
	{
		m_hitMapFlg = _flg;
	}

	const bool& GetHurtEnable()const
	{
		return m_hurtEnable;
	}
	void SetHurtEnable(bool _flg)
	{
		m_hurtEnable = _flg;
	}
	void SetHurtCold(const float& _time)
	{
		m_hurtCold = _time;
	}

	const bool& GetSlashFlg()const
	{
		return m_slashFlg;
	}
	void SetSlashFlg(bool _flg)
	{
		m_slashFlg = _flg;
	}

	void SetFire(bool _gunFireFlg)
	{
		m_gunFireFlg = _gunFireFlg;
	}
	const bool& GetFireFlg()const
	{
		return m_gunFireFlg;
	}

	void SetReload(bool _reloadFlg)
	{
		m_reloadFlg = _reloadFlg;
	}
	const bool& GetReloadFlg()const
	{
		return m_reloadFlg;
	}

	const int GetTakeBulletNum()const
	{
		return m_bulletNum;
	}
	void SetTakeBulletNum(const int& _num)
	{
		m_bulletNum += _num;
	}

	const int& GetFireEnableBulletNum()const
	{
		return m_fireEnableBulletNum;
	}
	void SetFireEnableBulletNum(const int& _num)
	{
		m_fireEnableBulletNum += _num;
	}

	std::vector<Potion*>& GetPotion()
	{
		return m_potion;
	}
	const bool& GetHealFlg()const
	{
		return m_healFlg;
	}
	void SetHealFlg(bool _flg)
	{
		m_healFlg = _flg;
	}
	const float& GetHealWaitTime()const
	{
		return m_healWaitTime;
	}

	void AddPotion(Potion* _potion)
	{
		m_potion.push_back(_potion);
	}

	const PlayerState& GetPlayerState()const
	{
		return m_playerState;
	}
	void SetPlayerState(const PlayerState& _state)
	{
		m_playerState = _state;
	}

private:
	bool m_camLockFlg;
	bool m_aliveFlg;
	bool m_moveFlg;
	bool m_hitMapFlg;
	bool m_dieMotionFlg;
	float m_dissolvePow;

	float m_hpMax;
	float m_hp;
	float m_speed;
	float m_acceleration;
	float m_hurtCold;
	bool m_hurtEnable;

	//ノックバック関係
	bool m_knockBackFlg;
	//ノックバックの方向
	Math::Vector3 m_knockBackVec;
	float m_knockBackPow;

	PlayerState m_playerState;
	bool m_slashFlg;
	float m_swordDamage;

	bool m_gunFireFlg;
	float m_gunDamage;
	bool m_reloadFlg;
	int m_bulletNum;
	int m_fireEnableBulletNum;
	int m_bulletOutNum;

	std::vector<Potion*> m_potion;
	bool m_healFlg;
	float m_healWaitTime;


};
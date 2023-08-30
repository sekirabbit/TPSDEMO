#pragma once

#include"ObjectBase.h"
class GameScene;
class HPBar;

class Enemy :public ObjectBase
{
public:
	Enemy();
	virtual ~Enemy();
	virtual void Update()override;
	void Draw()override;

	void SetEnemyType(EnemyType _type);
	void SetOwner(GameScene* _gameScene);
	void DieMotion();
	void Dissove();
	void HitAbout();
	void EnemyHitAvoid();
	void PlayerHitAvoid();
	void SwordHit();
	void KnockBack();
	void HPChange(const float& _damage);
	void SetKnockBack(bool _flg, const Math::Vector3& _backVec, const float& _backPow)
	{
		m_knockBackFlg = _flg;
		m_knockBackVec = _backVec;
		m_knockBackPow = _backPow;
	}
	virtual bool CheckEnemy(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec)const;

	const EnemyType& GetEnemyType()const
	{
		return m_enemyType;
	}
	void SetHitModel(KdModel* _model)
	{
		m_model = _model;
	}

	Enemy_body& GetEnemyBody()
	{
		return*m_body;
	}

	const bool& GetDieMotionFlg()const
	{
		return m_dieMotionFlg;
	}
	void SetDieMotionFlg(bool _flg)
	{
		m_dieMotionFlg = _flg;
	}

	const bool& GetAlive()const
	{
		return m_aliveFlg;
	}
	void SetAlive(bool _flg)
	{
		m_aliveFlg = _flg;
	}

	const bool& GetAngry()const
	{
		return m_angryFlg;
	}

	void SetAttack(bool _flg)
	{
		m_attackFlg = _flg;
	}
	const float& GetHP()const
	{
		return m_hp;
	}
	const float& GetHPMax()const
	{
		return m_hpMax;
	}
	void SetAngry(bool _flg)
	{
		m_angryFlg = _flg;
	}

	const EnemyState& GetCurrentStateType()const
	{
		return m_stateType;
	}
	void SetCurrentState(BaseState* _state)
	{
		m_currentState = _state;
	}
	void SetStateType(const EnemyState& _type)
	{
		m_stateType = _type;
	}

	void ChangerColor(Math::Vector3 _rgb)
	{
		m_changeColor += _rgb;
	}

	const float& GetToPlayerDist()const
	{
		return m_toPlayerDist;
	}

	std::list<Dizzy*>& GetDizzy()
	{
		return m_dizzy;
	}


	Vomit& GetVomit()
	{
		return *m_vomit;
	}

	HPBar& GetHPBar()
	{
		return *m_hpBar;
	}
protected:
	bool m_aliveFlg;
	bool m_angryFlg;

	bool m_attackFlg;
	Math::Vector3 m_changeColor;

	float m_hp;
	float m_hpMax;
	float m_breakHP;
	float m_breakHPMax;

	float m_hitWaitTime;
	float m_beWeakDamage;

	bool m_knockBackFlg;
	Math::Vector3 m_knockBackVec;
	float m_knockBackPow;

	bool m_dieMotionFlg;
	float m_dissolvePow;

	float m_toPlayerDist;

	EnemyType m_enemyType;
	EnemyState m_stateType;
	BaseState* m_currentState = nullptr;//現在のステート
	//weakステート表現
	std::list<Dizzy*> m_dizzy;
	Vomit* m_vomit;

	private:
	HPBar* m_hpBar;
	Enemy_body* m_body;
	Enemy_hand* m_hand;
	Enemy_leftLeg* m_leftLeg;
	Enemy_rightLeg* m_rightLeg;

};
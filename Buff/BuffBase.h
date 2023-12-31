#pragma once

class GameScene;
//Buffの基底クラス
class BuffBase
{
public:
	BuffBase();
	virtual bool Update();

	const KdTexture* GetBuffTex()const
	{
		return m_buff;
	}
	const BuffName& GetBuffName()const
	{
		return m_buffName;
	}
	const bool GetAlive()const
	{
		return m_aliveFlg;
	}
	const float GetLastTime()const
	{
		return m_currentLifeTime;
	}
	const float GetAlpha()const
	{
		return m_alpha;
	}
	
protected:
	GameScene* m_gameScene;
	KdTexture* m_buff;
	ObjType m_buffTaker;
	BuffName m_buffName;
	
	//寿命
	float m_lifeTime;
	float m_currentLifeTime;
	//Buff判定ために用意する変数
	bool m_aliveFlg;

	float m_alpha;
	
};
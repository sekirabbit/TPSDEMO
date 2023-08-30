#pragma once

class GameScene;
//Buff�̊��N���X
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
	
	//����
	float m_lifeTime;
	float m_currentLifeTime;
	//Buff���肽�߂ɗp�ӂ���ϐ�
	bool m_aliveFlg;

	float m_alpha;
	
};
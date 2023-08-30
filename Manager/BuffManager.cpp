#include "BuffManager.h"

BuffManager::BuffManager(GameScene* _gameScene)
{
	m_List.clear();
	m_gameScene = _gameScene;
}

BuffManager::~BuffManager()
{
	for (auto i = 0; i < m_List.size(); i++)
	{
		delete m_List[i];
		m_List[i] = nullptr;
	}
	m_List.clear();
}

void BuffManager::Update()
{
	for (auto i = 0; i < m_List.size(); i++)
	{
		if (m_List[i]->Update() == false)
		{
			delete m_List[i];
			//②枠を消す
			m_List.erase(m_List.begin() + i);
			//③カウンタ変数を戻す
			i--;
		}
	}
}

void BuffManager::Add(BuffBase* _buff)
{
	for (auto i = 0; i < m_List.size(); i++)
	{
		//追加したいBuffと本来であるBuff同じなら、旧Buffを覆う（寿命更新）
		if (m_List[i]->GetBuffName() == _buff->GetBuffName())
		{
			delete m_List[i];
			//②枠を消す
			m_List.erase(m_List.begin() + i);
			//③カウンタ変数を戻す
			i--;
		}
	}
	m_List.push_back(_buff);
}

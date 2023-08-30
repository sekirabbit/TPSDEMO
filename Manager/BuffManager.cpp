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
			//�A�g������
			m_List.erase(m_List.begin() + i);
			//�B�J�E���^�ϐ���߂�
			i--;
		}
	}
}

void BuffManager::Add(BuffBase* _buff)
{
	for (auto i = 0; i < m_List.size(); i++)
	{
		//�ǉ�������Buff�Ɩ{���ł���Buff�����Ȃ�A��Buff�𕢂��i�����X�V�j
		if (m_List[i]->GetBuffName() == _buff->GetBuffName())
		{
			delete m_List[i];
			//�A�g������
			m_List.erase(m_List.begin() + i);
			//�B�J�E���^�ϐ���߂�
			i--;
		}
	}
	m_List.push_back(_buff);
}

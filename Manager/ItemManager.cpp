#include "Headers.h"

ItemManager::ItemManager(GameScene* _gameScene)
{
	m_List.clear();
	m_gameScene = _gameScene;
	//マップにアイテムを配置する
	Math::Vector3 pos(-70, 0, 60);
	AddItem(new Potion(m_gameScene, pos));
	pos.z -= 2;
	AddItem(new Ammo(m_gameScene, pos));
	pos = Math::Vector3(28, 0, 95);
	AddItem(new Ammo(m_gameScene, pos));

}

ItemManager::~ItemManager()
{
	for (auto i = 0; i < m_List.size(); i++)
	{
		delete m_List[i];
		m_List[i] = nullptr;
	}
	m_List.clear();
}

void ItemManager::Update()
{
	for (auto i = 0; i < m_List.size(); i++)
	{
		m_List[i]->Update();
	}

	for (auto i = 0; i < m_List.size(); i++)
	{
		if (m_List[i]->GetAlive() == false)
		{
			delete m_List[i];
			//②枠を消す
			m_List.erase(m_List.begin() + i);
			//③カウンタ変数を戻す
			i--;
		}
	}
}

void ItemManager::Draw()
{
	SHADER.m_standardShader.SetToDevice();

	for (auto i = 0; i < m_List.size(); i++)
	{
		m_List[i]->Draw();
	}
}

void ItemManager::AddItem(ItemBase* _item)
{
	m_List.push_back(_item);
}

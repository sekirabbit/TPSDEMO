#include"Headers.h"

EffectManager::EffectManager(GameScene* _gameScene)
{
	m_List.clear();
	m_gameScene = _gameScene;
}

void EffectManager::Update()
{
	auto it = m_List.begin();
	while (it != m_List.end())
	{
		if ((*it)->Update() == false)
		{
			delete(*it);
			it = m_List.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EffectManager::Draw()
{
	SHADER.m_effectShader.SetToDevice();

	for (auto& obj : m_List)
	{
		obj->Draw();
	}
}

EffectManager::~EffectManager()
{
	for (auto& obj : m_List)
	{
		delete obj;
	}
	m_List.clear();
}

void EffectManager::Add(EffectBase* _effect)
{
	m_List.push_back(_effect);
}

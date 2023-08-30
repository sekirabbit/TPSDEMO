#pragma once

class GameScene;

class EffectManager
{
public:
	EffectManager(GameScene* _gameScene);
	~EffectManager();

	void Draw();
	void Update();

	void Add(EffectBase* _effect);

	std::list<EffectBase*>& GetEffect()
	{
		return m_List;
	}

private:
	GameScene* m_gameScene;

	std::list<EffectBase*> m_List;
};
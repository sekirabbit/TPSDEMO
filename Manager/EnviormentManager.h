#pragma once

class GameScene;

class EnviormentManager
{
public:
	EnviormentManager(GameScene* _gameScene);
	~EnviormentManager();

	void Draw();
	void Update();
	void AddTree(Tree* _tree);
	void AddSwamp(Swamp* _swamp);
	const bool GetHitMapDrawEnable()
	{
		return m_hitMapDrawFlg;
	}
	void SetHitMapDrawEnable(bool _flg)
	{
		m_hitMapDrawFlg = _flg;
	}

	Bilud& GetBilud()
	{
		return *m_bilud;
	}
	Bridge& GetBridge()
	{
		return *m_bridge;
	}
	Fences& GetFences()
	{
		return *m_fences;
	}
	Ground& GetGround()
	{
		return *m_ground;
	}
	River& GetRiver()
	{
		return *m_river;
	}
	HitMap& GetHitMap()
	{
		return *m_hitMap;
	}
	std::vector<Tree*>& GetTree()
	{
		return m_tree;
	}
	std::list<Swamp*>& GetSwamp()
	{
		return m_swamp;
	}
private:
	GameScene* m_gameScene;
	
	SkyDome* m_skyDome;
	Ground* m_ground;
	River* m_river;
	Fences* m_fences;
	Bilud* m_bilud;
	Bridge* m_bridge;
	BossDoor* m_bossDoor;
	HitMap* m_hitMap;
	std::list<Swamp*> m_swamp;
	std::vector<Tree*> m_tree;

	bool m_hitMapDrawFlg;
};
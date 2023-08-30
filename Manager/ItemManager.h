#pragma once

class GameScene;

class ItemManager
{
public:
	ItemManager(GameScene* _gameScene);
	~ItemManager();

	void Update();
	void Draw();

	void AddItem(ItemBase* _item);

	std::vector<ItemBase*>& GetItem()
	{
		return m_List;
	}
private:
	GameScene* m_gameScene;

	std::vector<ItemBase*> m_List;

};
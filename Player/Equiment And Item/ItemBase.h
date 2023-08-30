#pragma once

class ItemBase :public ObjectBase
{
public:
	void Update()override;
	void Draw()override;

protected:
	ItemType m_itemType;
};
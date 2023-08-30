#include "Headers.h"

Potion::Potion(GameScene* _gameScene, const Math::Vector3& _pos)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Item/Potion.gltf");
	m_itemType = ItemType::Potion;
	m_pos = _pos;
	m_aliveFlg = true;
	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
}

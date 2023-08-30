#include "Headers.h"

Ammo::Ammo(GameScene* _gameScene, const Math::Vector3& _pos)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Item/ammoBox.gltf");
	m_itemType = ItemType::Ammo;

	m_pos = _pos;
	m_aliveFlg = true;
	Math::Matrix mat = DirectX::XMMatrixScaling(7, 7, 7);
	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 1.0f, m_pos.z);
	m_worldMat = mat * m_worldMat;
}

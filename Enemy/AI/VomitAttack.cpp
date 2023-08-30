#include "Headers.h"

BaseState* VomitAttack::Action(Enemy* _enemy, GameScene* _gameScene)
{
	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	//’e‚Ì‰ŠúÝ’è
	Math::Vector3 intPos = DirectX::XMVector3TransformCoord(Math::Vector3{ 0,3,1 }, _enemy->GetMat());
	Math::Matrix mat = DirectX::XMMatrixScaling(1, 1, 1);
	mat = mat * DirectX::XMMatrixTranslation(intPos.x, intPos.y, intPos.z);
	Math::Vector3 dir = playerMan.GetPlayer().GetPos() - _enemy->GetPos();
	dir.Normalize();
	float movePow = EnemySetting::vomitSpeed;
	_gameScene->GetEffectManager().Add(new Vomit(_gameScene, _enemy, mat, dir, movePow));
	//se
	auto vomitSE = _gameScene->GetSound().GetVomitAttackSE();
	auto vomitSEInst = vomitSE->CreateInstance(true);
	vomitSEInst->SetVolume(1.0f);
	vomitSEInst->Play();

	_enemy->SetStateType(EnemyState::Track);
	return new Track();
}
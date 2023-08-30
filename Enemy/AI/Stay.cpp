#include "Headers.h"

BaseState* Stay::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}
	//�X�e�[�g��ԂɃ_���[�W���󂯂���g���b�N��Ԃɐ؂�ւ���
	if (_enemy->GetCurrentStateType() == EnemyState::Awake)
	{
		_enemy->SetStateType(EnemyState::Track);
		return new Track();
	}
	EnemyManager& enemyMan = _gameScene->GetEnemyManager();
	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	//�U���p�x�����߂�(�v���C���[�̎�O)
	Math::Vector3 targetVec = playerMan.GetPlayer().GetMat().Translation() - _enemy->GetMat().Translation();
	float enemyAngY = GetVecAngY(targetVec);

	float searchingRange;
	if (_enemy->GetEnemyType() == EnemyType::Boss)
	{
		searchingRange = BossSetting::searchingRange;
	}
	else
	{
		searchingRange = EnemySetting::searchingRange;
	}

	//�����̋����͈��͈͓̔��Ȃ画�肷��
	if (targetVec.Length() < searchingRange)
	{
		Math::Matrix mat = _enemy->GetMat();
		//�ڐ��ɓ�������X�e�[�g�ϊ�����
		if (TurnToAng(mat, enemyAngY, EnemySetting::focuTurnAng) <= EnemySetting::searchingAng && TurnToAng(mat, enemyAngY, EnemySetting::focuTurnAng) > -EnemySetting::searchingAng)
		{
			_gameScene->GetEffectManager().Add(new Attention(_enemy));

			_enemy->SetStateType(EnemyState::Track);
			return new Track();
		}
		//�߂�����������X�e�[�g�ϊ�����
		if (targetVec.Length() < EnemySetting::awakeDis)
		{
			_gameScene->GetEffectManager().Add(new Attention(_enemy));

			_enemy->SetStateType(EnemyState::Track);
			return new Track();
		}
	}

	return nullptr;
}
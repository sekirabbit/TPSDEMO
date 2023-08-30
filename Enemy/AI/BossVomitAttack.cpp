#include "Headers.h"

BossVomitAttack::BossVomitAttack()
{
	//�o���e��
	m_outCubeNum = BossSetting::vomitNum;
	//����
	m_lastTime = m_outCubeNum * 60;
}

BaseState* BossVomitAttack::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}

	m_lastTime--;
	if (m_lastTime < 0)
	{
		_enemy->SetStateType(EnemyState::Track);
		return new Track();
	}

	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	//VomitAttack�̍U�����[�h�ݒ�
	//�G�̏Ə����v���C���[���݂̈ʒu�Ɉړ�����
	Math::Vector3 targetVec = playerMan.GetPlayer().GetMat().Translation() - _enemy->GetMat().Translation();
	float enemyAngY = GetVecAngY(targetVec);
	Math::Matrix mat = _enemy->GetMat();
	float ang = TurnToAng(mat, enemyAngY, EnemySetting::focuTurnAng);
	//Y����]��m_worldMat�ɍX�V
	_enemy->SetMat(mat);

	if (ang == 0)
	{
		//���ˎ��Ԃ�ݒ�
		int currentTime = m_lastTime % 60;
		if (currentTime == 0)
		{
			int cubeNum = m_lastTime / 60;
			//�e�̏����ݒ�
			Math::Vector3 intPos = _enemy->GetPos() + Math::Vector3{ 0, 2, 0 };

			Math::Vector3 dir = _gameScene->GetPlayerManager().GetPlayer().GetPos() - _enemy->GetPos();
			dir.Normalize();
			float movePow;
			if (_enemy->GetEnemyType() == EnemyType::Boss)
			{
				movePow = BossSetting::vomitSpeed;
				if (_enemy->GetAngry())
				{
					movePow = BossSetting::angryVomitSpeed;
				}
			}
			else
			{
				movePow = EnemySetting::vomitSpeed;
			}
			Math::Matrix mat = DirectX::XMMatrixTranslation(intPos.x, intPos.y, intPos.z);
			
			//se
			auto vomitSE = _gameScene->GetSound().GetVomitAttackSE();
			auto vomitSEInst = vomitSE->CreateInstance(true);
			vomitSEInst->SetVolume(1.0f);
			vomitSEInst->Play();

			_gameScene->GetEffectManager().Add(new Vomit(_gameScene, _enemy, mat, dir, movePow));
		}
	}
	
	return nullptr;
}
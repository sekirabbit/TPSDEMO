#include "Headers.h"

AttackWait::AttackWait()
{
	m_lastTime = EnemySetting::attackWaitTime;
	m_bloodNum = 1;

	m_attackModel;
}

BaseState* AttackWait::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}
	//������ǂ����O�ɕ���
	Math::Matrix mat = _enemy->GetMat();
	Math::Matrix transMat;
	transMat = DirectX::XMMatrixTranslation(0, 0, EnemySetting::focuSpeed / 2);
	mat = transMat * mat;
	_enemy->SetMat(mat);

	//�U�������̃G�t�F�N�g�𐶐�
	if (_enemy->GetEnemyType() == EnemyType::Boss)
	{
		for (int i = 0; i < m_bloodNum; i++)
		{
			//�����x�N�g�������߂�				�@ �G�̍��W��荂���Ƃ��납��
			Math::Vector3 vec = _enemy->GetPos() + Math::Vector3(0, 3.5f, 0);
			//											�����_���ŏo�����W��ݒ肷��
			Math::Vector3 bloodPos = Math::Vector3{ (float)(rand() % 15 - 7),(float)(rand() % 15 - 7) ,(float)(rand() % 15 - 7) };
			bloodPos += vec;
			//�G�ɐڋ߂��������ݒ肷��
			Math::Vector3 pointBloodMoveDir = vec - bloodPos;
			float Dist = pointBloodMoveDir.Length();
			pointBloodMoveDir.Normalize();
			//���Ԃɂ����size�������ɍs��
			float bloodSize = 0.3f * (m_lastTime / EnemySetting::attackWaitTime);
			float alpha = 1 / Dist + 0.3f;
			_gameScene->GetEffectManager().Add(new PointBlood(bloodPos, pointBloodMoveDir, EffectSetting::bloodLifeTime, alpha, bloodSize));
		}
	}
	//�X�e�[�g�������������鋤�ɐ����G�t�F�N�g����ǉ�
	if ((int)m_lastTime % 10 == 0)
	{
		m_bloodNum += 1;
	}
	if (_enemy->GetEnemyType() == EnemyType::Normal)
	{
		//�U���������G�̐F��ς��
		_enemy->ChangerColor(Math::Vector3{ 0.02f,0,0 });
	}
	if (_enemy->GetEnemyType() == EnemyType::Smoker)
	{
		_enemy->ChangerColor(Math::Vector3{ 0,0.02f,0 });
	}
	if (m_lastTime <= 0)
	{
		if (_enemy->GetEnemyType() == EnemyType::Boss)
		{
			////Boss�̍U�����[�h�������_���őI��
			int num = rand() % BossSetting::skillUsePossible;
			if (num < (BossSetting::skillUsePossible / 2))
			{
				if (_enemy->GetAngry())
				{
					num = rand() % 3;
					if (num < 1)
					{
						_enemy->SetStateType(EnemyState::VomitAttack);
						return new BossVomitAttack();
					}
					else
					{
						//Boss���W�ɑ�ʂ̓ŉ��𐶐�����
						//���W��K���ɒ�������
						Math::Vector3 smokePos = _enemy->GetPos();

						Math::Color color = { 0.2f,0.5f,0.2f,1.0f };
						float size = 3.0f;
						_gameScene->GetEffectManager().Add(new Smoke(smokePos, color, size));
						
						_enemy->SetStateType(EnemyState::Nova);
						return new DrugNova();
					}
				}
				else
				{
					_enemy->SetStateType(EnemyState::VomitAttack);
					return new BossVomitAttack();
				}
				
				
			}
			if (num >= (BossSetting::skillUsePossible / 2))
			{
				//se
				auto vomitSE = _gameScene->GetSound().GetVomitAttackSE();
				auto vomitSEInst = vomitSE->CreateInstance(true);
				vomitSEInst->SetVolume(1.0f);
				vomitSEInst->Play();

				_enemy->SetStateType(EnemyState::Attack);
				return new BossDashAttack();
			}
				
				
		}
		else
		{
			auto attackSE = _gameScene->GetSound().GetEnemyAwakeSE();
			auto seInst = attackSE->CreateInstance(true);
			seInst->SetVolume(0.05f);
			seInst->Play();
			if (_enemy->GetEnemyType() == EnemyType::Smoker)
			{
				_enemy->SetStateType(EnemyState::VomitAttack);
				return new VomitAttack();
			}
			else
			{
				_enemy->SetStateType(EnemyState::Attack);
				return new DashAttack();
			}
		}
	}
	m_lastTime--;

	return nullptr;
}

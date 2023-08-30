#include"Headers.h"

Enemy::Enemy()
{
	m_objType = ObjType::Enemy;
	m_aliveFlg = true;
	m_angryFlg = false;
	//�U�����鎞�Ƀ��f���̐F�ύX���邽�ߕϐ�
	m_changeColor = Math::Vector3{ 0.1f,0.1f,0.1f };

	m_hpMax = EnemySetting::maxHp;
	m_hp = m_hpMax;
	m_breakHPMax = EnemySetting::breakHP;
	m_breakHP = m_breakHPMax;

	m_hitWaitTime = EnemySetting::hitWaitTime;

	//�m�b�N�o�b�N�֌W�ϐ�
	m_knockBackFlg = false;
	m_knockBackVec = {};
	m_knockBackPow = 0;
	//���S�A�j���[�V�����֌W�ϐ�
	m_dieMotionFlg = false;
	m_dissolvePow = 0;

	m_toPlayerDist = 0;

	m_currentState = new Stay();
	m_stateType = EnemyState::Stay;

	m_dizzy.clear();
	m_hpBar = new HPBar(this);
	m_body = new Enemy_body(m_gameScene, this);
	m_hand = new Enemy_hand(m_gameScene, this);
	m_leftLeg = new Enemy_leftLeg(m_gameScene, this);
	m_rightLeg = new Enemy_rightLeg(m_gameScene, this);
}

void Enemy::Update()
{
	Math::Vector3 targetVec = m_gameScene->GetPlayerManager().GetPlayer().GetPos() - m_pos;
	m_toPlayerDist = targetVec.Length();

	//���͈͓̔������A�b�v�f�[�g����
	if (m_toPlayerDist <= 50.0f)
	{
		m_hpBar->Update();

		if (m_aliveFlg == true)
		{
			if (m_hp <= 0)
			{
				SHADER.m_standardShader.SetDissolvePower(0);
				//���S�A�j���[�V�����ݒ�
				m_startMat = m_worldMat;
				//�A�j���[�V�����̃G���h�}�b�g��ǂɓ���Ȃ��悤�ɓ����蔻�肷��
				Math::Vector3 lookVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), m_worldMat);
				lookVec.Normalize();
				m_pos -= lookVec * 3;
				HitObj(ObjName::HitMap, m_gameScene, -lookVec);
				Math::Matrix transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
				Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(-90));
				m_endMat = rotMat * transMat;
				m_animeFrame = 0;

				//���S�\��SE
				auto deadSE = m_gameScene->GetSound().GetEnemyDeadSE();
				auto deadSEInst = deadSE->CreateInstance(true);
				deadSEInst->SetVolume(0.5f);
				deadSEInst->Play();

				//�A�C�e���o��SE
				auto se = m_gameScene->GetSound().GetItemOutSE();
				auto seInst = se->CreateInstance(false);
				seInst->Play();
				Math::Vector3 itemPos = m_worldMat.Translation();
				if (m_enemyType == EnemyType::Normal)
				{
					m_gameScene->GetItemManager().AddItem(new Ammo(m_gameScene, itemPos));
				}
				if (m_enemyType == EnemyType::Smoker)
				{
					m_gameScene->GetItemManager().AddItem(new Potion(m_gameScene, itemPos));
				}

				m_aliveFlg = false;
				m_dieMotionFlg = true;
			}
			//�G��AI
			if (m_currentState != nullptr)
			{
				BaseState* nextState;
				//���[���h���ōs�����X�V����
				nextState = m_currentState->Action(this, m_gameScene);

				//�ʂ̃X�e�[�g�ւ̈ڍs��]���A���Ă���
				if (nextState != nullptr)
				{
					//���݂̃X�e�[�g���폜
					delete m_currentState;
					//�ڍs������݂̃X�e�[�g�Ƃ���
					m_currentState = nextState;
				}
			}

			//AI���s�Ȍ��m_pos���X�V
			m_pos = m_worldMat.Translation();
			//AI�Ń��[���h���W��ύX�����Ȍ�̉�]�p�x�����߂�
			m_ang = GetVecAngY(DirectX::XMVector3TransformNormal(Math::Vector3{ 0,0,1 }, m_worldMat));
			HitAbout();
		}
		else
		{
			if (m_dieMotionFlg == true)
			{
				DieMotion();
			}
		}

		m_body->Update();
		m_hand->Update();
		m_leftLeg->Update();
		m_rightLeg->Update();
	}
}

Enemy::~Enemy()
{
	if (m_currentState != nullptr)
	{
		delete m_currentState;
	}

	for (auto& dizzy : m_dizzy)
	{
		delete dizzy;
	}
	m_dizzy.clear();

	delete m_hpBar;
	delete m_body;
	delete m_hand;
	delete m_leftLeg;
	delete m_rightLeg;
}

void Enemy::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	if (m_aliveFlg == true)
	{
		if (m_stateType == EnemyState::AttackWait)
		{
			SHADER.m_standardShader.SetColor(m_changeColor.x, m_changeColor.y, m_changeColor.z);
			SHADER.m_standardShader.SetColorEnable(true);
		}
		else
		{
			//�F�ύX�̏����ݒ�ɖ߂�
			m_changeColor = Math::Vector3{ 0.1f,0.1f,0.1f };
			SHADER.m_standardShader.SetColorEnable(false);
			if (m_stateType == EnemyState::Weak)
			{
				for (auto& dizzy : m_dizzy)
				{
					dizzy->Draw();
				}
			}
		}
	}
	else
	{
		if (m_dieMotionFlg)
		{
			SHADER.m_standardShader.SetDissolveEnable(true);
		}
	}
	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 1.0f,0.2f,0.2f });
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetDitherEnable(false);
	m_body->Draw();
	m_hand->Draw();
	m_leftLeg->Draw();
	m_rightLeg->Draw();
	SHADER.m_standardShader.SetDitherEnable(true);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetDissolveEnable(false);
	SHADER.m_standardShader.SetColorEnable(false);
	SHADER.m_standardShader.SetLimLightEnable(false);
}

void Enemy::KnockBack()
{
	if (m_knockBackFlg == true)
	{
		float rate = 0.75f;
		Math::Vector3 BackVec = m_knockBackVec * m_knockBackPow;
		m_pos += BackVec;
		BackVec.Normalize();
		HitObj(ObjName::HitMap, m_gameScene, BackVec);
		PosToMat();
		m_knockBackPow *= rate;
		if (m_knockBackPow <= 0.01f)
		{
			m_knockBackPow = 0;
			m_knockBackVec = {};
			m_knockBackFlg = false;
		}
	}
}
void Enemy::HPChange(const float& _damage)
{
	m_hp += _damage;
	if (m_hp <= 0)
	{
		m_hp = 0;
	}

	if (m_breakHP > 0)
	{
		m_breakHP += _damage;
		if (m_breakHP <= 0)
		{
			m_stateType = EnemyState::Weak;
			m_dizzy.push_back(new Dizzy(this));
			if (m_enemyType == EnemyType::Boss)
			{
				//���̃X�^���h��ԂɂȂ邽�߂ɗ^����_���[�W��{���ŏグ��
				m_breakHPMax *= 2.5f;
			}
			m_breakHP = m_breakHPMax;
		}
	}

}
bool Enemy::CheckEnemy(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec) const
{
	if (ModelIntersects(*m_model, m_worldMat, _rayPos, _rayVec, _dis, _normalVec))
	{
		return true;
	}
	return false;
}

void Enemy::DieMotion()
{
	//�Ō��G�t�F�N�g�̐���
		//�����x�N�g�������߂�				�@ �G�̍��W��荂���Ƃ����
	Math::Vector3 vec = m_worldMat.Translation() + Math::Vector3(0, 1, 0);
	//											�����_���ŏo�����W��ݒ肷��
	Math::Vector3 bloodPos = Math::Vector3{ (float)(rand() % 5 - 2),(float)(rand() % 5 - 2) ,(float)(rand() % 5 - 2) };
	bloodPos += vec;
	//�G���痣��������ݒ肷��
	Math::Vector3 pointBloodMoveDir = bloodPos - vec;
	pointBloodMoveDir.Normalize();
	float alpha = 1 - m_dissolvePow;
	float bloodSize = 0.2f;
	m_gameScene->GetEffectManager().Add(new PointBlood(bloodPos, pointBloodMoveDir, EffectSetting::bloodLifeTime, alpha, bloodSize));

	if (m_enemyType != EnemyType::Boss)
	{
		//���S�A�j���[�V����
		AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
		m_animeFrame += 0.05f;

		if (m_animeFrame >= 1.0f)
		{
			m_animeFrame = 1.0f;
			//�f�B�U�����O�قڏI��鎞�ɁA�G�̍��W��Swamp�𐶐�����
			float size = 0.01f;
			m_gameScene->GetEnviormentManager().AddSwamp(new Swamp(m_gameScene, m_worldMat.Translation(), size));
		
			Dissove();
		}
	}
	else
	{
		Dissove();
	}

	
}

void Enemy::Dissove()
{
	m_dissolvePow += 0.005f;
	SHADER.m_standardShader.SetDissolvePower(m_dissolvePow);

	if (m_dissolvePow > 1.0f)
	{
		m_dissolvePow = 1.0f;
		m_dieMotionFlg = false;
		//boss�G�̃f�B�U�����O���I��鎞�ɃQ�[���N���A���肷��
		if (m_enemyType == EnemyType::Boss)
		{
			m_gameScene->GetEnemyManager().SetClearFlg(true);
		}

	}
}

void Enemy::HitAbout()
{
	FallDown(m_gameScene);
	KnockBack();
	EnemyHitAvoid();
	PlayerHitAvoid();
	//�X�^���h��ԕ\��
	if (m_stateType == EnemyState::Weak)
	{
		//�X�V
		for (auto dizzy : m_dizzy)
		{
			dizzy->Update();
		}
		//�폜
		auto it = m_dizzy.begin();
		while (it != m_dizzy.end())
		{
			if ((*it)->GetAlive() == false)
			{
				delete(*it);
				it = m_dizzy.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	if (m_hitWaitTime == 0)
	{
		SwordHit();
	}
	else
	{
		m_hitWaitTime--;
		if (m_hitWaitTime < 0)
		{
			m_hitWaitTime = 0;
		}
	}
	HitObj(ObjName::HitMap, m_gameScene);
	PosToMat();
}

void Enemy::EnemyHitAvoid()
{
	EnemyManager& enemyMan = m_gameScene->GetEnemyManager();
	//�G�ƓG���d�˂�h�~
	for (UINT i = 0; i < enemyMan.GetEnemy().size(); i++)
	{
		if (enemyMan.GetEnemy()[i]->GetAlive() == true)
		{
			//����enemy���̂ł͂Ȃ��ꍇ�Ŕ��肷��
			if (enemyMan.GetEnemy()[i] != this)
			{
				Math::Vector3 targetVec = enemyMan.GetEnemy()[i]->GetPos() - m_pos;
				targetVec.y = 0;
				if (targetVec.Length() <= EnemySetting::toEnemyLimitDis)
				{
					float pushPow = EnemySetting::toEnemyLimitDis - targetVec.Length();
					m_moveVec += targetVec;
					m_moveVec.Normalize();
					m_moveVec *= pushPow;
					//�����͂ŁA�����͑��Ε����Ɉړ�����
					m_moveVec *= 0.5f;
					enemyMan.GetEnemy()[i]->AddPos(m_moveVec);
					m_pos += -m_moveVec;
					Math::Vector3 vec = -m_moveVec;
					vec.Normalize();
					HitObj(ObjName::HitMap, m_gameScene, vec);
					PosToMat();
				}
			}
		}
	}
}

void Enemy::PlayerHitAvoid()
{
	//�d�˂�h�~�i�v���C���[�j
	Math::Vector3 currentPos = m_pos;
	Math::Vector3 targetVec = m_gameScene->GetPlayerManager().GetPlayer().GetPos();
	targetVec = targetVec - currentPos;
	float limitDis;
	if (m_enemyType == EnemyType::Boss)
	{
		limitDis = BossSetting::toPlayerLimitDis;
	}
	else
	{
		limitDis = EnemySetting::toPlayerLimitDis;
	}
	if (targetVec.Length() <= limitDis)
	{
		float pushPow = limitDis - targetVec.Length();

		m_moveVec += targetVec;
		m_moveVec.Normalize();
		m_moveVec *= pushPow;
		m_moveVec *= 0.5f;

		m_pos += -m_moveVec;
		Math::Vector3 vec = -m_moveVec;
		vec.Normalize();
		HitObj(ObjName::HitMap, m_gameScene, vec);
		PosToMat();
		m_gameScene->GetPlayerManager().GetPlayer().AddPos(m_moveVec);
		m_gameScene->GetPlayerManager().GetPlayer().HitObj(ObjName::HitMap, m_gameScene, -vec);
	}
}

void Enemy::SwordHit()
{
	//�����蔻��i���j
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	if (playerMan.GetPlayer().GetSlashFlg() == true)
	{
		float modelRadius;
		if (m_enemyType != EnemyType::Boss)
		{
			modelRadius = 3.0f;
		}
		else
		{
			modelRadius = 5.0f;
		}
		if (AttackCheck(playerMan.GetSword().GetPos(), m_worldMat.Translation(), modelRadius))
		{
			auto se = m_gameScene->GetSound().GetSlashHitSEInst();
			se->Play(false);
			bool isWeakState = false;
			float damage = EquitSetting::swordDamage;
			if (m_stateType == EnemyState::Weak)
			{
				isWeakState = true;
				damage = EquitSetting::swordDamage * EquitSetting::weakAttackRate;
			}
			else
			{
				isWeakState = false;
			}
			HPChange(damage);
			m_gameScene->GetEffectManager().Add(new DamageNum(m_pos, damage, isWeakState));
			m_hitWaitTime = EnemySetting::hitWaitTime;
			if (m_enemyType != EnemyType::Boss)
			{
				//���̐���											//���W��肿����ƍ����Ƃ����
				Math::Vector3 bloodPos = m_worldMat.Translation() + Math::Vector3(0, 3.5f, 0);
				m_gameScene->GetEffectManager().Add(new Blood(bloodPos));
				for (int i = 0; i < 2; i++)
				{
					//��]�s����쐬(���_���΂������������_���Ɍ��߂�)
					//�����_���ŕ����̉�]�s���ݒu
					float angX, angY, angZ;
					angX = DirectX::XMConvertToRadians((float)(rand() % 360));
					angY = DirectX::XMConvertToRadians((float)(rand() % 360));
					angZ = DirectX::XMConvertToRadians((float)(rand() % 360));
					Math::Matrix rotMat = DirectX::XMMatrixRotationRollPitchYaw(angX, angY, angZ);
					//�����x�N�g�������߂�
					Math::Vector3 pointBloodMoveDir = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), rotMat);
					m_gameScene->GetEffectManager().Add(new PointBlood(bloodPos, pointBloodMoveDir, EffectSetting::bloodLifeTime));
				}

				//�v���C���[�̍U�������Ƀm�b�N�o�b�N
				Math::Vector3 targetVec;
				targetVec = m_gameScene->GetPlayerManager().GetPlayer().GetMat().Translation() - m_worldMat.Translation();
				targetVec.Normalize();
				float backPow = EquitSetting::slashBackPow;
				SetKnockBack(true, -targetVec, backPow);
			}

			if (m_stateType == EnemyState::Stay)
			{
				m_stateType = EnemyState::Awake;
			}
		}
	}
}

void Enemy::SetEnemyType(EnemyType _type)
{
	m_enemyType = _type;
}

void Enemy::SetOwner(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
}

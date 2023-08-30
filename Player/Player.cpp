#include"Headers.h"

Player::Player(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_objType = ObjType::Player;

	m_model = RESOURCE.GetModel("Data/Player/Player.gltf");
	m_localMat = Math::Matrix::Identity;

	//初期座標
	m_pos = { 0,0,0 };
	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	//初期設定
	m_camLockFlg = false;
	m_aliveFlg = true;
	m_dieMotionFlg = false;

	m_ang = 0;
	m_speed = 0;
	//加速度
	m_acceleration = PlayerSetting::acceleration;
	m_hpMax = PlayerSetting::maxHp;
	m_hp = m_hpMax;
	m_hitMapFlg = true;
	m_hurtCold = 0;
	m_hurtEnable = true;
	//ノックバック設定
	m_knockBackFlg = false;
	m_knockBackVec = {};
	m_knockBackPow = 0;
	//剣設定
	m_slashFlg = false;
	m_swordDamage = EquitSetting::swordDamage;
	m_playerState = PlayerState::Stay;
	//銃設定
	m_gunFireFlg = false;
	m_reloadFlg = false;
	m_gunDamage = EquitSetting::gunDamage;
	//予備弾丸数
	m_bulletNum = PlayerSetting::takeBulletNum;
	m_fireEnableBulletNum = PlayerSetting::fireEnableBulletNum;
	//出す弾数
	m_bulletOutNum = EquitSetting::outBulletNum;
	//ポーション関係
	m_healFlg = false;
	m_healWaitTime = 0;

	for (int i = 0; i < PlayerSetting::takePotionMaxNum; i++)
	{
		m_potion.push_back(new Potion(m_gameScene, Math::Vector3::Zero));
	}
}

void Player::AddPos(const Math::Vector3& _pos)
{
	m_pos += _pos;
	Math::Vector3 lookVec = DirectX::XMVector3TransformNormal(Math::Vector3{ 0,0,1 }, m_worldMat);
	HitObj(ObjName::HitMap, m_gameScene, lookVec);
}

void Player::Update(float _camAngY)
{
	if (m_aliveFlg)
	{
		//アクション更新
		HitObj(ObjName::River, m_gameScene);
		HitObj(ObjName::Swamp, m_gameScene);
		HitObj(ObjName::Bridge, m_gameScene);
		Control(_camAngY);
		KnockBack();
		FallDown(m_gameScene);
		Slash();
		Shot();
		Reload();
		DrinkPotion();
		//ダメージ受けれる判定
		m_hurtCold--;
		if (m_hurtCold <= 0)
		{
			m_hurtCold = 0;
			m_hurtEnable = true;
		}
	}
	else
	{
		if (m_dieMotionFlg)
		{
			DieMotion();
		}
	}
}

void Player::Control(const float& _ang)
{
	//ラジコン操作
	Math::Vector3 moveVec = {};
	m_moveFlg = false;
	if (m_slashFlg == false)
	{
		if (m_gameScene->GetPlayerManager().GetPlayerRShoulder().GetSlashWaitTime() <= 0)
		{
			if (m_moveFlg == false)
			{
				if (m_gameScene->GetEnemyManager().GetBossApear() == false)
				{
					if (GetAsyncKeyState('W') & 0x8000)
					{
						moveVec += MoveVec(_ang, Math::Vector3(0, 0, m_speed));
						m_moveFlg = true;
					}
					if (GetAsyncKeyState('S') & 0x8000)
					{
						moveVec += MoveVec(_ang, Math::Vector3(0, 0, -m_speed));
						m_moveFlg = true;
					}
					if (GetAsyncKeyState('A') & 0x8000)
					{
						moveVec += MoveVec(_ang, Math::Vector3(-m_speed, 0, 0));
						m_moveFlg = true;
					}
					if (GetAsyncKeyState('D') & 0x8000)
					{
						moveVec += MoveVec(_ang, Math::Vector3(m_speed, 0, 0));
						m_moveFlg = true;
					}
				}
			}
		}
	}

	if (m_moveFlg == true)
	{
		if (m_gameScene->GetEnemyManager().GetBossApear() == false)
		{
			//移動中MoveSEを使用
			m_gameScene->GetSound().GetWalkSEInst()->SetVolume(0.3f);
			m_gameScene->GetSound().GetWalkSEInst()->Resume();
		}

		m_speed += m_acceleration;
		if (m_speed >= PlayerSetting::maxSpeed)
		{
			m_speed = PlayerSetting::maxSpeed;
		}
		EnviormentManager& enviorMan = m_gameScene->GetEnviormentManager();

		moveVec.Normalize();
		//移動ベクトルでマップに当たり判定する
		HitObj(ObjName::HitMap, m_gameScene, moveVec);
		moveVec *= m_speed;

		m_pos += moveVec;
		Math::Matrix nowRotaMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));
		Math::Vector3 nowVec = XMVector3TransformNormal(Math::Vector3(0, 0, 1), nowRotaMat);

		Math::Vector3 toVec = moveVec;
		toVec.Normalize();

		//内積（回転する角度を求める）
		Math::Vector3 dot = DirectX::XMVector3Dot(nowVec, toVec);

		if (dot.x > 1)
		{
			dot.x = 1.0f;
		}
		if (dot.x < -1)
		{
			dot.x = -1.0f;
		}

		float ang = DirectX::XMConvertToDegrees(acos(dot.x));

		if (ang >= 0.1f)
		{
			if (ang > 9)
			{
				ang = 9.0f;
			}
		}

		//外積（どっちに回転するかを調べる）
		Math::Vector3 cross = DirectX::XMVector3Cross(toVec, nowVec);
		cross.Normalize();

		if (cross.y >= 0)
		{
			m_ang -= (ang * 1.5f);
		}
		else
		{
			m_ang += (ang * 1.5f);
		}
		//ー－－－－－－－－－－－－－－－－－－－－－－－－－
	}
	else
	{
		m_speed = 0;
		m_gameScene->GetSound().GetWalkSEInst()->Pause();

	}
	Math::Matrix rotaMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));
	Math::Matrix transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	m_worldMat = rotaMat * transMat;
}

void Player::KnockBack()
{
	if (m_knockBackFlg == true)
	{
		float rate = 0.75f;
		Math::Vector3 BackVec = m_knockBackVec * m_knockBackPow;
		m_pos += BackVec;
		BackVec.Normalize();
		//マップと当たり判定する用のベクトルを入れる
		HitObj(ObjName::HitMap, m_gameScene, BackVec);
		m_knockBackPow *= rate;
		if (m_knockBackPow <= 0.01f)
		{
			m_knockBackPow = 0;
			m_knockBackVec = {};
			m_knockBackFlg = false;
		}
	}
}

void Player::SetKnockBack(bool _flg, const Math::Vector3& _backVec, const float& _backPow)
{
	m_knockBackFlg = _flg;
	m_knockBackVec = _backVec;
	m_knockBackPow = _backPow;
}

void Player::Slash()
{
	if (m_gameScene->GetEnemyManager().GetBossApear() == false)
	{
		//剣攻撃
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (SYSTEM.GetSlashKeyFlg() == false)
			{
				SYSTEM.SetSlashKeyFlg(true);
				m_slashFlg = true;
			}

		}
		else
		{
			SYSTEM.SetSlashKeyFlg(false);
		}
	}

}
void Player::Shot()
{
	if (m_gunFireFlg == false && m_reloadFlg == false)
	{
		if (m_gameScene->GetEnemyManager().GetBossApear() == false)
		{
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				if (SYSTEM.GetFireKeyFlg() == false)
				{
					SYSTEM.SetFireKeyFlg(true);
					//持つブレットを減少
					if (m_fireEnableBulletNum - 1 >= 0)
					{
						m_gunFireFlg = true;
					}
					else
					{
						//一回だけSEを起動する
						auto se = m_gameScene->GetSound().GetLockSEInst();
						se->Play(false);
					}
					if (m_gunFireFlg == true)
					{
						//一回だけSEを起動する
						auto se = m_gameScene->GetSound().GetFireSE();
						auto seInst = se->CreateInstance(true);
						seInst->SetVolume(0.5f);
						seInst->Play(false);
						//出すブレットを生成
						PlayerManager& playerMan = m_gameScene->GetPlayerManager();
						//エフェクト追加位置の設定
						Math::Matrix mat = playerMan.GetGunBarrel().GetMat();
						Math::Matrix transMat = DirectX::XMMatrixTranslation(-0.4f, 0.4f, 0);
						Math::Matrix tmpMat;
						tmpMat = transMat * mat;
						m_gameScene->GetEffectManager().Add(new Fire(tmpMat.Translation()));
						m_gameScene->GetEffectManager().Add(new Smoke(tmpMat.Translation()));

						for (int i = 0; i < m_bulletOutNum; i++)
						{
							//ランダムで弾方向の回転行列を設置
							float angX, angY, angZ;
							angX = DirectX::XMConvertToRadians((float)(rand() % 90 - 60));
							angY = DirectX::XMConvertToRadians((float)(rand() % 120 - 30));
							angZ = 0;
							Math::Matrix rotMat = DirectX::XMMatrixRotationRollPitchYaw(angX, angY, angZ);
							//弾の移動ベクトルを合成
							Math::Vector3 moveVec = DirectX::XMVector3TransformNormal(GetLookVec(0, m_ang), rotMat);
							m_gameScene->GetEffectManager().Add(new Bullet(m_gameScene, tmpMat.Translation(), moveVec, rotMat));
						}
					}
				}
			}
			else
			{
				SYSTEM.SetFireKeyFlg(false);
			}
		}
	}

	if (m_bulletNum < 0)
	{
		m_bulletNum = 0;
	}

}

void Player::Reload()
{
	if (m_gunFireFlg == false && m_reloadFlg == false)
	{
		if (m_gameScene->GetEnemyManager().GetBossApear() == false)
		{
			if (GetAsyncKeyState('R') & 0x8000)
			{
				if (SYSTEM.GetReloadKeyFlg() == false)
				{
					SYSTEM.SetReloadKeyFlg(true);
					if (m_bulletNum >= 1 && m_fireEnableBulletNum <= 1)
					{
						m_reloadFlg = true;
						auto se = m_gameScene->GetSound().GetReloadSE();
						auto seInst = se->CreateInstance(true);
						seInst->SetVolume(0.5f);
						seInst->Play(false);
					}
					else
					{
						m_reloadFlg = false;
						auto se = m_gameScene->GetSound().GetLockSE();
						auto seInst = se->CreateInstance(true);
						seInst->SetVolume(0.5f);
						seInst->Play(false);
					}
				}
			}
			else
			{
				SYSTEM.SetReloadKeyFlg(false);
			}
		}
	}

}

bool Player::CheckPlayer(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec) const
{
	Math::Matrix checkMat = DirectX::XMMatrixTranslation(0, 2, 0);
	checkMat = checkMat * m_worldMat;
	if (ModelIntersects(*m_model, checkMat, _rayPos, _rayVec, _dis, _normalVec))
	{
		return true;
	}
	return false;
}

bool Player::DieMotion()
{
	AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
	m_animeFrame += 0.01f;

	if (m_animeFrame > 1.0f)
	{
		m_animeFrame = 1.0f;
		return true;
	}

	return false;
}

void Player::HPChange(const float& _changePow)
{
	if (m_aliveFlg)
	{
		m_hp += _changePow;
		if (m_hp < 0)
		{
			//死亡アニメーション設定
			m_startMat = m_worldMat;
			Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90));
			m_endMat = rotMat * m_worldMat;
			m_animeFrame = 0;

			auto se = m_gameScene->GetSound().GetDeadSEInst();
			se->Play();

			m_hp = 0;
			m_aliveFlg = false;
			m_moveFlg = false;
			m_dieMotionFlg = true;
		}
		if (m_hp > PlayerSetting::maxHp)
		{
			m_hp = PlayerSetting::maxHp;
		}
	}

}

void Player::DrinkPotion()
{
	if (m_gameScene->GetEnemyManager().GetBossApear() == false)
	{
		if (GetAsyncKeyState('E') & 0x8000)
		{
			if (SYSTEM.GetHealKeyFlg() == false)
			{
				SYSTEM.SetHealKeyFlg(true);
				if (m_healWaitTime <= 0)
				{
					if (!m_potion.empty())
					{
						m_healFlg = true;
						m_gameScene->GetBuffManager().Add(new Heal(m_gameScene, ObjType::Player, EquitSetting::potionHealPower));
						m_gameScene->GetSound().GetDrinkSEInst()->Play(false);
						m_healWaitTime = PlayerSetting::usePotionWaitTime;
						int potionNum = m_potion.size();
						//最後目のポーション実体を消す
						delete m_potion.back();
						//枠を消す
						m_potion.erase(m_potion.begin() + (potionNum - 1));
					}
				}
			}
		}
		else
		{
			SYSTEM.SetHealKeyFlg(false);
		}
	}
	m_healWaitTime -= 1;
	if (m_healWaitTime < 0)
	{
		m_healWaitTime = 0;
		m_healFlg = false;
	}

}


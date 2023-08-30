#include"Headers.h"

Bullet::Bullet(GameScene* _gameScene, const Math::Vector3& _intPos, const Math::Vector3& _dir, const Math::Matrix& _rotMat)
{
	m_gameScene = _gameScene;
	m_tex = RESOURCE.GetTexture("Data/Effect/gunfire.png");

	m_pos = _intPos;
	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	//板ポリゴンの移動ベクトル方向に回転行列を調整する
	m_worldMat = _rotMat * m_worldMat;

	//板ポリゴン自身の回転行列を調整する
	Math::Matrix rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90));
	Math::Matrix rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_gameScene->GetPlayerManager().GetPlayer().GetAng()));

	m_worldMat = rotXMat * rotYMat * m_worldMat;

	m_lifeTime = EquitSetting::bulletCountTime;
	m_size = EquitSetting::bulletWidth;
	m_alpha = EquitSetting::bulletAlpha;

	Vertex v[4];

	float size_rate = EquitSetting::bulletLength;
	//描画順番、弾の前端から後ろに描画する
	v[0].pos = { -m_size,m_size,0 };
	v[1].pos = { m_size,m_size,0 };
	v[2].pos = { -m_size,-m_size * size_rate,0 };
	v[3].pos = { m_size,-m_size * size_rate,0 };

	v[0].color = { 1,1,1,m_alpha };
	v[1].color = { 1,1,1,m_alpha };
	v[2].color = { 1,1,1,m_alpha };
	v[3].color = { 1,1,1,m_alpha };

	v[0].uv = { 0,0 };
	v[1].uv = { 1,0 };
	v[2].uv = { 0,1 };
	v[3].uv = { 1,1 };

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = v;

	m_vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);

	m_moveVec = _dir;
	m_moveVec.Normalize();

}

Bullet::~Bullet()
{
	m_vb.Release();
}

bool Bullet::Update()
{
	//５フレイム一回判定する
	if (m_lifeTime % 5 == 0)
	{
		if (EnemyHit() == true)
		{
			return false;
		}
	}

	float movePow = EquitSetting::bulletSpeed;
	m_worldMat._41 += m_moveVec.x * movePow;
	m_worldMat._42 += m_moveVec.y * movePow;
	m_worldMat._43 += m_moveVec.z * movePow;

	m_lifeTime--;
	if (m_lifeTime <= 0)
	{
		return false;
	}

	return true;
}

void Bullet::Draw()
{
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
	D3D.GetDevContext()->OMSetBlendState(m_blendAdd, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);


	SHADER.m_effectShader.SetToDevice();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_vb.GetAddress(), &stride, &offset);

	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_tex->GetSRViewAddress());

	SHADER.m_effectShader.SetWorldMatrix(m_worldMat);
	SHADER.m_effectShader.WriteToCB();

	D3D.GetDevContext()->Draw(4, 0);

	D3D.GetDevContext()->OMSetBlendState(m_blendAlpha, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}

bool Bullet::EnemyHit()
{
	EnemyManager& enemyMan = m_gameScene->GetEnemyManager();

	//Bossへの当たり判定
	if (enemyMan.GetBoss()->GetAlive() == true)
	{
		Math::Vector3 rayPos = m_pos;
		Math::Vector3 rayVec = m_moveVec;
		float dist;
		Math::Vector3 bossNormal = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, -1), enemyMan.GetBoss()->GetMat());
		bool bossHit = enemyMan.GetBoss()->CheckEnemy(rayPos, rayVec, dist, bossNormal);
		if (bossHit == true && dist <= EquitSetting::bulletHitEnableDis)
		{
			//ノックバック
			rayVec.y = 0;
			bool isWeakState = false;
			float damage = EquitSetting::gunDamage;
			if (enemyMan.GetBoss()->GetCurrentStateType() == EnemyState::Weak)
			{
				isWeakState = true;
				damage = EquitSetting::gunDamage * EquitSetting::weakAttackRate;
			}
			else
			{
				isWeakState = false;
			}
			enemyMan.GetBoss()->HPChange(damage);
			m_gameScene->GetEffectManager().Add(new DamageNum(enemyMan.GetBoss()->GetPos(), damage, isWeakState));
			if (enemyMan.GetBoss()->GetCurrentStateType() == EnemyState::Stay)
			{
				enemyMan.GetBoss()->SetStateType(EnemyState::Awake);
			}
			return true;
		}
	}

	for (UINT i = 0; i < enemyMan.GetEnemy().size(); i++)
	{
		if (enemyMan.GetEnemy()[i]->GetAlive())
		{
			Math::Vector3 rayPos = m_pos;
			Math::Vector3 rayVec = m_moveVec;
			float dist;
			Math::Vector3 enemyNormal = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, -1), enemyMan.GetEnemy()[i]->GetMat());
			const bool enemyHit = enemyMan.GetEnemy()[i]->CheckEnemy(rayPos, rayVec, dist, enemyNormal);
			if (enemyHit == true && dist <= EquitSetting::bulletHitEnableDis)
			{
				//血の生成
				Math::Vector3 bloodPos = enemyMan.GetEnemy()[i]->GetMat().Translation() + Math::Vector3(0, 4, 0);
				m_gameScene->GetEffectManager().Add(new Blood(bloodPos));
				for (int i = 0; i < 2; i++)
				{
					//回転行列を作成(血点を飛ばす方向をランダムに決める)
					//ランダムで方向の回転行列を設置
					float angX, angY, angZ;
					angX = DirectX::XMConvertToRadians((float)(rand() % 360));
					angY = DirectX::XMConvertToRadians((float)(rand() % 360));
					angZ = DirectX::XMConvertToRadians((float)(rand() % 360));
					Math::Matrix rotMat = DirectX::XMMatrixRotationRollPitchYaw(angX, angY, angZ);
					//方向ベクトルを求める
					Math::Vector3 pointBloodMoveDir = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), rotMat);
					m_gameScene->GetEffectManager().Add(new PointBlood(bloodPos, pointBloodMoveDir, EffectSetting::bloodLifeTime));
				}
				//ノックバック
				rayVec.y = 0;
				float backPow = EquitSetting::shotBackPow;
				enemyMan.GetEnemy()[i]->SetKnockBack(true, rayVec, backPow);
				bool isWeakState = false;
				float damage = EquitSetting::gunDamage;
				if (enemyMan.GetEnemy()[i]->GetCurrentStateType() == EnemyState::Weak)
				{
					isWeakState = true;
					damage = EquitSetting::gunDamage * 2;
				}
				else
				{
					isWeakState = false;
				}
				enemyMan.GetEnemy()[i]->HPChange(damage);
				m_gameScene->GetEffectManager().Add(new DamageNum(enemyMan.GetEnemy()[i]->GetPos(), damage, isWeakState));
				//Stay状態にダメージを受けたら状態変更する
				if (enemyMan.GetEnemy()[i]->GetCurrentStateType() == EnemyState::Stay)
				{
					enemyMan.GetEnemy()[i]->SetStateType(EnemyState::Awake);
				}
				return true;
			}
		}

	}

	return false;
}






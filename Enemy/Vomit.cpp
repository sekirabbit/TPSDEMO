#include "Headers.h"

Vomit::Vomit(GameScene* _gameScene, Enemy* _enemy, const Math::Matrix& _mat, const Math::Vector3& _dir, const float& _movePow)
{
	m_gameScene = _gameScene;
	m_enemy = _enemy;

	m_pirpleGalax_cube = RESOURCE.GetModel("Data/Cube/pirpleGalax_cube.gltf");
	m_galax_cube = RESOURCE.GetModel("Data/Cube/galax_cube_02.gltf");
	m_pirple_cube = RESOURCE.GetModel("Data/Cube/pirple_cube.gltf");
	m_poison_cube = RESOURCE.GetModel("Data/Cube/poisonCube.gltf");

	m_blendAlpha = D3D.CreateBlendState(KdBlendMode::Alpha);
	m_blendAdd = D3D.CreateBlendState(KdBlendMode::Add);

	//Boss特の設定
	m_size = 5.5f;
	//初期設定
	m_pos = _mat.Translation();
	m_startPos = m_pos;
	m_worldMat = _mat;
	m_moveVec = _dir;
	float movePow = _movePow;
	//移動ベクトルの合成
	m_moveVec = m_moveVec * movePow;
	//寿命内の移動回数の計算
	Math::Vector3 targetVec = m_gameScene->GetPlayerManager().GetPlayer().GetPos() - _enemy->GetPos();
	float moveTimes = targetVec.Length() / m_moveVec.Length();
	//降りる量の計算
	m_moveVec.y = (m_gameScene->GetPlayerManager().GetPlayer().GetPos() - m_pos).y / moveTimes;
}

bool Vomit::Update()
{
	// UVスクロール---------------
	m_pirpleGalaxuvOffset.x -= 0.01f;
	m_pirpleGalaxuvOffset.y -= 0.01f;

	m_galaxuvOffset.x += 0.045f;
	m_galaxuvOffset.y += 0.045f;

	m_poisonuvOffset.x += 0.035f;
	m_poisonuvOffset.y -= 0.035f;
	// ---------------------------

	// 弾の移動 ------------------
	m_worldMat._41 += m_moveVec.x;
	m_worldMat._42 += m_moveVec.y;
	m_worldMat._43 += m_moveVec.z;
	m_pos = m_worldMat.Translation();
	// ---------------------------

	//-----------------------------------

	Math::Vector3 rayPos;
	Math::Vector3 rayVec;
	float dist;
	Math::Vector3 targetNormal;
	bool hit;
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	//当たり判定（プレイヤー）
	if (playerMan.GetPlayer().GetAlive())
	{
		if (playerMan.GetPlayer().GetHurtEnable())
		{
			Math::Vector3 playerHitCheckPos = playerMan.GetPlayer().GetPos();
			if (AttackCheck(m_pos, playerHitCheckPos, EnemySetting::vomitHitEnableDis))
			{
				Math::Vector3 dirVec = m_moveVec;
				dirVec.y = 0;
				float backPow = EnemySetting::vomitBackPower;
				playerMan.GetPlayer().SetKnockBack(true, dirVec, backPow);
				playerMan.GetPlayer().HPChange(EnemySetting::vomitPower);
				m_gameScene->GetBuffManager().Add(new Drug(m_gameScene, ObjType::Player));
				playerMan.GetPlayer().SetHurtEnable(false);
				playerMan.GetPlayer().SetHurtCold(PlayerSetting::hitWaitTime);

				auto se = m_gameScene->GetSound().GetHurtSEInst();
				se->Play();

				m_gameScene->SetBlurTime(PlayerSetting::blurTime);
				return false;
			}
		}
	}


	//当たり判定（地面）
	rayPos = m_pos;
	//移動方向でレイのベクトルに設定する
	rayVec = m_moveVec;
	rayVec.Normalize();
	rayVec = DirectX::XMVector3TransformNormal(rayVec, m_worldMat);
	rayVec.Normalize();
	targetNormal = DirectX::XMVector3TransformNormal(Math::Vector3{ 0,1,0 }, m_gameScene->GetEnviormentManager().GetGround().GetMat());
	targetNormal.Normalize();
	hit = m_gameScene->GetEnviormentManager().GetGround().CheckModel(rayPos, rayVec, dist, targetNormal);
	if (hit == true)
	{
		//球体の半径
		float cubeRadius = 0.5f;
		if (dist <= cubeRadius * 2)
		{
			Math::Matrix mat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + cubeRadius, m_pos.z);
			Math::Vector3 pos = Math::Vector3(m_pos.x, m_pos.y + cubeRadius, m_pos.z);
			m_gameScene->GetEnviormentManager().AddSwamp(new Swamp(m_gameScene, pos));
			return false;
		}
	}

	//橋
	hit = m_gameScene->GetEnviormentManager().GetBridge().CheckModel(rayPos, rayVec, dist, targetNormal);
	if (hit == true)
	{
		//球体の半径
		float cubeRadius = 0.5f;
		if (dist <= cubeRadius * 2)
		{
			Math::Matrix mat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + cubeRadius, m_pos.z);
			Math::Vector3 pos = Math::Vector3(m_pos.x, m_pos.y + cubeRadius, m_pos.z);
			m_gameScene->GetEnviormentManager().AddSwamp(new Swamp(m_gameScene, pos));
			return false;
		}
	}

	//当たり判定（マップ）
	rayPos = m_pos;
	rayVec = m_moveVec;
	rayVec.Normalize();
	rayVec = DirectX::XMVector3TransformNormal(rayVec, m_worldMat);
	rayVec.Normalize();
	targetNormal = DirectX::XMVector3TransformNormal(Math::Vector3{ 0,0,-1 }, m_gameScene->GetEnviormentManager().GetHitMap().GetMat());
	targetNormal.Normalize();
	hit = m_gameScene->GetEnviormentManager().GetHitMap().CheckModel(rayPos, rayVec, dist, targetNormal);
	if (hit == true)
	{
		Math::Vector3 dot = GetDot(targetNormal, rayVec);
		float limit = MapSetting::voimitAwayDistance / dot.x;
		if (limit < 0)
		{
			limit *= -1;
		}if (dist < limit) //壁までの距離が「立ち止まるべき距離」より短い
		{
			return false;
		}
	}


	return true;
}

bool Vomit::NovaModelUpdate(const float& _size,const float& _alpha)
{
	// UVスクロール---------------
	m_poisonuvOffset.x += 0.007f;
	m_poisonuvOffset.y += 0.005f;
	// ---------------------------

	m_alpha = _alpha;

	Math::Matrix mat = DirectX::XMMatrixScaling(_size, _size, _size);
	m_worldMat = m_enemy->GetMat() * Math::Matrix::CreateTranslation(0, 3.0f, 0);
	m_worldMat = mat * m_worldMat;

	return false;
}

void Vomit::NovaModelDraw()
{
	SHADER.m_standardShader.SetToDevice();

	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 0.2f,1.0f,0.2f });
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetColorEnable(false);
	SHADER.m_standardShader.SetDissolveEnable(true);

	Math::Matrix scale_02 = DirectX::XMMatrixScaling(1.1f, 1.1f, 1.1f);

	SHADER.m_standardShader.SetUVOffset(m_poisonuvOffset);

	SHADER.m_standardShader.SetWorldMatrix(scale_02 * m_worldMat);
	SHADER.m_standardShader.DrawModel(m_poison_cube, m_alpha);

	SHADER.m_standardShader.SetUVOffset(Math::Vector2(0, 0));

	SHADER.m_standardShader.SetDissolveEnable(false);
	SHADER.m_standardShader.SetColorEnable(false);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetDitherEnable(true);
	SHADER.m_standardShader.SetLimLightEnable(false);

}

void Vomit::Draw()
{
	SHADER.m_standardShader.SetToDevice();

	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 0.2f,1.0f,0.2f });
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetColor(0.5f, 1.0f, 0.5f);
	SHADER.m_standardShader.SetColorEnable(false);

	SHADER.m_standardShader.SetUVOffset(m_poisonuvOffset);

	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_poison_cube, 1.0f);

	SHADER.m_standardShader.SetUVOffset(Math::Vector2(0, 0));

	// pirplegalaxy ----------------------------------------------------------

	// ----------------------------------------------------------------------

	// galaxy ---------------------------------------------------------------
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
	D3D.GetDevContext()->OMSetBlendState(m_blendAdd, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);

	SHADER.m_standardShader.SetUVOffset(m_pirpleGalaxuvOffset);

	Math::Matrix scale_01 = DirectX::XMMatrixScaling(1.05f, 1.05f, 1.05f);
	SHADER.m_standardShader.SetColorEnable(true);

	SHADER.m_standardShader.SetWorldMatrix(scale_01 * m_worldMat);
	SHADER.m_standardShader.DrawModel(m_pirpleGalax_cube, 0.75f);
	SHADER.m_standardShader.SetUVOffset(Math::Vector2(0, 0));

	//// -----------------------------------------------------------------------

	// galax -----------------------------------------------------------------
	Math::Matrix scale_02 = DirectX::XMMatrixScaling(1.1f, 1.1f, 1.1f);

	SHADER.m_standardShader.SetUVOffset(m_galaxuvOffset);

	SHADER.m_standardShader.SetColorEnable(true);

	SHADER.m_standardShader.SetWorldMatrix(scale_02 * m_worldMat);
	SHADER.m_standardShader.DrawModel(m_galax_cube, 1.0f);

	SHADER.m_standardShader.SetUVOffset(Math::Vector2(0, 0));

	D3D.GetDevContext()->OMSetBlendState(m_blendAlpha, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
	// ------------------------------------------------------------------------
	SHADER.m_standardShader.SetDissolveEnable(false);
	SHADER.m_standardShader.SetColorEnable(false);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetDitherEnable(true);
	SHADER.m_standardShader.SetLimLightEnable(false);

}

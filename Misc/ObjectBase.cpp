#include"Headers.h"


ObjectBase::ObjectBase()
{
	m_worldMat = Math::Matrix::Identity;
	m_localMat = Math::Matrix::Identity;
	m_pos = { 0,0,0 };
	m_moveVec = {0,0,1};
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::Update()
{

}

void ObjectBase::Draw()
{
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 0.2f,0.2f,1.0f });
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLightEnable(false);
}

void ObjectBase::PosToMat()
{
	//m_pos変更した最後に合成する
	Math::Matrix rotaMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));
	Math::Matrix transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	m_worldMat = rotaMat * transMat;
}

bool ObjectBase::CheckModel(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec) const
{
	if (ModelIntersects(*m_model, m_worldMat, _rayPos, _rayVec, _dis, _normalVec))
	{
		return true;
	}
	return false;
}

void ObjectBase::HitObj(ObjName _obj, GameScene* _gameScene, const Math::Vector3& _rayVec)
{
	EnviormentManager& enviorMan = _gameScene->GetEnviormentManager();
	bool hit;
	float dist = 0;
	Math::Vector3 targetNormal;//レイが当たった面の法線
	Math::Vector3 rayPos;
	Math::Vector3 rayVec;
	if (_obj == ObjName::HitMap)
	{
		targetNormal = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, -1), enviorMan.GetHitMap().GetMat());
		targetNormal.Normalize();
		rayPos = m_pos + Math::Vector3{ 0,2,0 };
		//_rayVecが渡されてない場合は真っ正面のベクトルを使用する
		if (_rayVec.Length() == 0)
		{
			rayVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), m_worldMat);
		}
		else
		{
			rayVec = _rayVec;
		}
		rayVec.Normalize();
		hit = enviorMan.GetHitMap().CheckModel(rayPos, rayVec, dist, targetNormal);
		if (hit)
		{
			Math::Vector3 dot = GetDot(targetNormal, rayVec);
			float limit = MapSetting::playerAwayDistance / dot.x;
			if (limit < 0)
			{
				limit *= -1;
			}if (dist < limit) //壁までの距離が「立ち止まるべき距離」より短い
			{
				Math::Vector3 moveVec = targetNormal * ((limit - dist) * dot.x);
				moveVec.y = 0;
				m_pos += moveVec;
			}
		}
	}
	if (_obj == ObjName::River)
	{
		targetNormal = DirectX::XMVector3TransformNormal(Math::Vector3(0, 1, 0), enviorMan.GetRiver().GetMat());
		targetNormal.Normalize();
		rayPos = m_pos + Math::Vector3{0,2.5f,0};
		rayVec = DirectX::XMVector3TransformNormal(Math::Vector3{ 0,-1,0 }, m_worldMat);
		rayVec.Normalize();
		hit = enviorMan.GetRiver().CheckModel(rayPos, rayVec, dist, targetNormal);
		if (hit)
		{
			Math::Vector3 dot = GetDot(targetNormal, rayVec);
			float limit = MapSetting::playerAwayDistance / dot.x;
			if (limit < 0)
			{
				limit *= -1;
			}
			if (dist <= limit)
			{
				_gameScene->GetBuffManager().Add(new Drug(_gameScene, ObjType::Player));
			}
		}
	}
	if (_obj == ObjName::Swamp)
	{
		for (auto& swamp : enviorMan.GetSwamp())
		{
			//消す条件はAlphaので、違和感ないように大分透明になったら当たり判定しない
			if (swamp->GetAlpha() >= 0.3f)
			{
				Math::Vector3 playerPos = _gameScene->GetPlayerManager().GetPlayer().GetPos();
				playerPos.y = 0;
				Math::Vector3 swampPos = swamp->GetPos();
				swampPos.y = 0;
				Math::Vector3 targetVec = playerPos - swampPos;
				//scaling行列のsize引数によって判定距離を変更する
				if (targetVec.Length() <= (2.0f * swamp->GetSize()))
				{
					_gameScene->GetBuffManager().Add(new Drug(_gameScene, ObjType::Player));
				}
			}
		}
	}
}

bool ObjectBase::FallDown(GameScene* _gameScene)
{
	EnviormentManager& enviorMan = _gameScene->GetEnviormentManager();
	float dist;
	Math::Vector3 targetNormal;//レイが当たった面の法線
	targetNormal = DirectX::XMVector3TransformNormal(Math::Vector3(0, 1, 0), enviorMan.GetGround().GetMat());
	Math::Vector3 rayVec = Math::Vector3{ 0,-1,0 };
	Math::Vector3 rayPos = m_pos + Math::Vector3{ 0,1,0 };
	bool hit = enviorMan.GetBridge().CheckModel(rayPos, rayVec, dist, Math::Vector3{ 0,1,0 });
	if (hit)
	{
		m_pos.y = rayPos.y - dist;
	}
	else
	{
		//地面と再判定する際に座標を沈むないように上昇する
		m_pos.y += 2;
		targetNormal = DirectX::XMVector3TransformNormal(Math::Vector3(0, 1, 0), enviorMan.GetGround().GetMat());
		rayVec = Math::Vector3{ 0,-1,0 };
		rayPos = m_pos + Math::Vector3{ 0,1,0 };
		hit = enviorMan.GetGround().CheckModel(rayPos, rayVec, dist, Math::Vector3{ 0,1,0 });
		if (hit)
		{
			m_pos.y = rayPos.y - dist;
		}
	}

	return true;
}

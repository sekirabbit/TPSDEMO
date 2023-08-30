#include "Headers.h"


DamageNum::DamageNum(const Math::Vector3& _intPos, const float& _damage, bool _isWeakDamage)
{
	m_normalMath = RESOURCE.GetTexture("Data/Texture/UI/yellow_math_icon.png");
	m_weakMath = RESOURCE.GetTexture("Data/Texture/UI/red_math_icon.png");

	m_isWeakDamage = _isWeakDamage;

	m_transparentBeginTime = 60;
	m_size = 0.4f;
	m_alpha = 1.0f;

	m_pos = _intPos;
	m_pos.x += (float)(rand() % 10) * 0.1f;
	m_pos.y += (5 + (float)(rand() % 10) * 0.1f);
	m_TenMat = DirectX::XMMatrixIdentity();
	m_UintMat = DirectX::XMMatrixIdentity();

	m_damage = -_damage;

	if (m_damage / 10 >= 1.0f)
	{
		m_damageTenFlg = true;
	}
	else
	{
		m_damageTenFlg = false;
	}
}
DamageNum::~DamageNum()
{
	m_tenVb.Release();
	m_uintVb.Release();
}

bool DamageNum::Update()
{
	m_transparentBeginTime--;
	if (m_transparentBeginTime < 0)
	{
		m_alpha -= 0.05f;
		if (m_alpha <= 0)
		{
			m_alpha = 0;
			return false;
		}
		m_pos.y += 0.1f;
	}
	else
	{
		m_pos.y += 0.05f;
	}


	Math::Matrix tmpMat = SHADER.m_cb7_Camera.Work().mV;

	tmpMat._41 = 0;
	tmpMat._42 = 0;
	tmpMat._43 = 0;

	tmpMat = tmpMat.Invert();

	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	m_worldMat = tmpMat * m_worldMat;

	Vertex v[4];
	D3D11_SUBRESOURCE_DATA srd = {};

	//ダメージの十位
	if (m_damageTenFlg)
	{
		int damageTen = (int)m_damage / 10 % 10;

		v[0].pos = { -m_size,m_size,0 };
		v[1].pos = { m_size,m_size,0 };
		v[2].pos = { -m_size,-m_size,0 };
		v[3].pos = { m_size,-m_size,0 };

		v[0].color = { 1,1,1,m_alpha };
		v[1].color = { 1,1,1,m_alpha };
		v[2].color = { 1,1,1,m_alpha };
		v[3].color = { 1,1,1,m_alpha };

		v[0].uv = { ((float)damageTen / 10),0 };
		v[1].uv = { ((float)(damageTen + 1) / 10),0 };
		v[2].uv = { ((float)damageTen / 10),0.5f };
		v[3].uv = { ((float)(damageTen + 1) / 10),0.5f };

		srd.pSysMem = v;
		m_tenVb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);

		Math::Matrix mat = DirectX::XMMatrixTranslation(-m_size * 1.5f, 0, 0);

		m_TenMat = mat * m_worldMat;


	}
	//ダメージの最小位

	int damageUint = (int)m_damage / 1 % 10;

	v[0].pos = { -m_size,m_size,0 };
	v[1].pos = { m_size,m_size,0 };
	v[2].pos = { -m_size,-m_size,0 };
	v[3].pos = { m_size,-m_size,0 };

	v[0].color = { 1,1,1,m_alpha };
	v[1].color = { 1,1,1,m_alpha };
	v[2].color = { 1,1,1,m_alpha };
	v[3].color = { 1,1,1,m_alpha };

	v[0].uv = { ((float)damageUint / 10),0 };
	v[1].uv = { ((float)(damageUint + 1) / 10),0 };
	v[2].uv = { ((float)damageUint / 10),0.5f };
	v[3].uv = { ((float)(damageUint + 1) / 10),0.5f };

	srd.pSysMem = v;

	m_uintVb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);

	m_UintMat = m_worldMat;

	
	

	return true;
}

void DamageNum::Draw()
{
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(false, false), 0);


	SHADER.m_effectShader.SetToDevice();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	KdTexture* texture;
	if (m_isWeakDamage)
	{
		texture = m_weakMath;
	}
	else
	{
		texture = m_normalMath;
	}


	//ダメージの十位
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_tenVb.GetAddress(), &stride, &offset);

	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, texture->GetSRViewAddress());

	SHADER.m_effectShader.SetWorldMatrix(m_TenMat);
	SHADER.m_effectShader.WriteToCB();

	D3D.GetDevContext()->Draw(4, 0);


	//ダメージの最小位
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_uintVb.GetAddress(), &stride, &offset);

	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, texture->GetSRViewAddress());

	SHADER.m_effectShader.SetWorldMatrix(m_UintMat);
	SHADER.m_effectShader.WriteToCB();

	D3D.GetDevContext()->Draw(4, 0);

	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}





#include "Headers.h"


PointBlood::PointBlood(const Math::Vector3& _intPos, const Math::Vector3& _dirVec, const float& _aliveTime, const float& _alpha, const float& _size)
{
	m_tex = RESOURCE.GetTexture("Data/Effect/BloodPoint.png");
	m_size = _size;
	m_alpha = _alpha;
	m_aliveTime = _aliveTime;

	m_pos = _intPos;

	Vertex v[4];

	v[0].pos = { -m_size,m_size,0 };
	v[1].pos = { m_size,m_size,0 };
	v[2].pos = { -m_size,-m_size,0 };
	v[3].pos = { m_size,-m_size,0 };

	float rgb_r;
	rgb_r = 0.1f;
	v[0].color = { rgb_r,1,1,m_alpha };
	v[1].color = { rgb_r,1,1,m_alpha };
	v[2].color = { rgb_r,1,1,m_alpha };
	v[3].color = { rgb_r,1,1,m_alpha };

	v[0].uv = { 0,0 };
	v[1].uv = { 1,0 };
	v[2].uv = { 0,1 };
	v[3].uv = { 1,1 };

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = v;

	m_vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);

	Math::Matrix tmpMat = SHADER.m_cb7_Camera.Work().mV;

	tmpMat._41 = 0;
	tmpMat._42 = 0;
	tmpMat._43 = 0;

	tmpMat = tmpMat.Invert();

	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	m_worldMat = tmpMat * m_worldMat;

	float movePow = 0.1f;
	m_moveVec = _dirVec * movePow;
	//èdóÕ
	m_gravity = 0.1f;

}
PointBlood::~PointBlood()
{
	m_vb.Release();
}

bool PointBlood::Update()
{
	m_worldMat._41 += m_moveVec.x;
	m_worldMat._42 += m_moveVec.y;
	m_worldMat._43 += m_moveVec.z;

	m_aliveTime--;
	if (m_aliveTime < 0)
	{
		return false;
	}
	return true;
}

void PointBlood::Draw()
{
	SHADER.m_effectShader.SetToDevice();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_vb.GetAddress(), &stride, &offset);

	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_tex->GetSRViewAddress());
	SHADER.m_effectShader.SetWorldMatrix(m_worldMat);
	SHADER.m_effectShader.WriteToCB();

	D3D.GetDevContext()->Draw(4, 0);

}





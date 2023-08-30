#include "Headers.h"


Smoke::Smoke(const Math::Vector3& _intPos, const Math::Color& _color, const float& _size)
{
	m_tex = RESOURCE.GetTexture("Data/Effect/smoke5.png");
	m_pos = _intPos;

	m_color = _color;

	m_size = _size;
	m_alpha = m_color.w;
}

Smoke::~Smoke()
{
	m_vb.Release();
}

bool Smoke::Update()
{
	Vertex v[4];

	v[0].pos = { -m_size,m_size,0 };
	v[1].pos = { m_size,m_size,0 };
	v[2].pos = { -m_size,-m_size,0 };
	v[3].pos = { m_size,-m_size,0 };

	v[0].color = { m_color.x,m_color.y,m_color.z,m_alpha };
	v[1].color = { m_color.x,m_color.y,m_color.z,m_alpha };
	v[2].color = { m_color.x,m_color.y,m_color.z,m_alpha };
	v[3].color = { m_color.x,m_color.y,m_color.z,m_alpha };

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

	m_pos.y += 0.05f;

	m_size += 0.02f;

	m_alpha -= 0.01f;
	if (m_alpha <= 0)
	{
		m_alpha = 0;
		return false;
	}
	return true;
}
void Smoke::Draw()
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




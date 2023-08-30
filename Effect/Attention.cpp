#include "Headers.h"


Attention::Attention(const ObjectBase* _obj)
{
	m_tex = RESOURCE.GetTexture("Data/Texture/UI/attention.png");
	m_size = 0.6f;
	m_alpha = 1.0f;

	m_pos = {};
	m_obj = _obj;
}
Attention::~Attention()
{
	m_vb.Release();
}

bool Attention::Update()
{
	//ˆÊ’u’²®
	m_pos = m_obj->GetPos() + Math::Vector3(0,6,0);
	m_alpha -= 0.02f;
	if (m_alpha < 0)
	{
		return false;
	}

	Vertex v[4];

	v[0].pos = { -m_size,m_size,0 };
	v[1].pos = { m_size,m_size,0 };
	v[2].pos = { -m_size,-m_size,0 };
	v[3].pos = { m_size,-m_size,0 };

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

	Math::Matrix tmpMat = SHADER.m_cb7_Camera.Work().mV;

	tmpMat._41 = 0;
	tmpMat._42 = 0;
	tmpMat._43 = 0;

	tmpMat = tmpMat.Invert();

	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	m_worldMat = tmpMat * m_worldMat;



	return true;
}

void Attention::Draw()
{
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(false, false), 0);

	SHADER.m_effectShader.SetToDevice();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_vb.GetAddress(), &stride, &offset);

	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_tex->GetSRViewAddress());

	SHADER.m_effectShader.SetWorldMatrix(m_worldMat);
	SHADER.m_effectShader.WriteToCB();

	D3D.GetDevContext()->Draw(4, 0);

	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}





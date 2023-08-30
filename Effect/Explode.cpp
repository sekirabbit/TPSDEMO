#include "Headers.h"

Explode::Explode(GameScene* _gameScene)
{
	m_gameScene = _gameScene;

	m_tex = RESOURCE.GetTexture("Data/Effect/weapon_trail.png");
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	m_worldMat = playerMan.GetSword().GetMat();
	//初期座標を設定する
	for (int i = 0; i < texNum; i++)
	{
		m_slowMat[i] = m_worldMat;
	}

	Vertex v[texNum * 2];

	m_vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DYNAMIC, nullptr);

	m_size = 2.0f;
	m_alpha = 1.0f;
	m_lifeTime = 10.0f;
}

Explode::~Explode()
{
	m_vb.Release();
}
bool Explode::Update()
{
	//座標の更新
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	m_worldMat = playerMan.GetSword().GetMat();
	//頂点情報の更新

	Vertex v[texNum * 2];

	for (int i = 0; i < texNum; i++)
	{
		v[i * 2 + 0].pos = DirectX::XMVector3TransformCoord(Math::Vector3(0, -m_size, 0), m_slowMat[i]);
		v[i * 2 + 1].pos = DirectX::XMVector3TransformCoord(Math::Vector3(0, m_size, 0), m_slowMat[i]);

		v[i * 2 + 0].color = { 1,1,1,m_alpha };
		v[i * 2 + 1].color = { 1,1,1,m_alpha };

		v[i * 2 + 0].uv = { 0,(float)i / (float)(texNum - 1) };
		v[i * 2 + 1].uv = { 1,(float)i / (float)(texNum - 1) };

	}

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = v;

	//履歴を残す処理
	m_slowMat[0] = m_worldMat;
	for (int i = texNum - 1; i > 0; i--)
	{
		m_slowMat[i] = m_slowMat[i - 1];
	}
	//	 書き込み  左上の配列からまとめて
	m_vb.WriteData(&v[0], sizeof(v));

	//剣を振るのアニメ終わる直前にエフェクトを削除する
	if (playerMan.GetPlayer().GetSlashFlg() == false)
	{
		return false;
	}
	return true;


}


void Explode::Draw()
{
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
	D3D.GetDevContext()->OMSetBlendState(m_blendAdd, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	SHADER.m_effectShader.SetToDevice();

	SHADER.m_effectShader.SetWorldMatrix(Math::Matrix::Identity);

	SHADER.m_effectShader.WriteToCB();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_vb.GetAddress(), &stride, &offset);
	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_tex->GetSRViewAddress());

	D3D.GetDevContext()->Draw(texNum * 2, 0);

	D3D.GetDevContext()->OMSetBlendState(m_blendAlpha, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}





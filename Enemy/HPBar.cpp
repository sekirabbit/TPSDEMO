#include "Headers.h"


HPBar::HPBar(Enemy* _enemy)
{
	m_enemy = _enemy;

	m_enemyHP = RESOURCE.GetTexture("Data/Texture/UI/enemy_HPBar.png");
	m_enemyHPEmpty = RESOURCE.GetTexture("Data/Texture/UI/enemy_HPBar_empty.png");
}
HPBar::~HPBar()
{
	m_vb.Release();
	m_emptyVb.Release();
}

bool HPBar::Update()
{
	//emptyHPBarのVertexの設置
	Vertex v[4];

	v[0].pos = { 0,0.2f,0 };
	v[1].pos = { 4.0f,0.2f,0 };
	v[2].pos = { 0,-0.2f,0 };
	v[3].pos = { 4.0f,-0.2f,0 };

	v[0].color = { 1,1,1,1 };
	v[1].color = { 1,1,1,1 };
	v[2].color = { 1,1,1,1 };
	v[3].color = { 1,1,1,1 };

	v[0].uv = { 0,0 };
	v[1].uv = { 1,0 };
	v[2].uv = { 0,1 };
	v[3].uv = { 1,1 };

	D3D11_SUBRESOURCE_DATA srd = {};

	srd.pSysMem = v;

	m_emptyVb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);


	//実際のHPBarのVertexの設置
	float length = m_enemy->GetHP() / m_enemy->GetHPMax();

	v[0].pos = { 0,0.2f,0 };
	v[1].pos = { length * 4.0f,0.2f,0 };
	v[2].pos = { 0,-0.2f,0 };
	v[3].pos = { length * 4.0f,-0.2f,0 };

	v[0].color = { 1,1,1,1 };
	v[1].color = { 1,1,1,1 };
	v[2].color = { 1,1,1,1 };
	v[3].color = { 1,1,1,1 };

	v[0].uv = { 0,0 };
	v[1].uv = { 1,0 };
	v[2].uv = { 0,1 };
	v[3].uv = { 1,1 };

	srd.pSysMem = v;

	m_vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);

	Math::Matrix tmpMat = SHADER.m_cb7_Camera.Work().mV;

	tmpMat._41 = 0;
	tmpMat._42 = 0;
	tmpMat._43 = 0;

	tmpMat = tmpMat.Invert();

	m_pos = m_enemy->GetPos();
	//敵の頭の上に座標を設定する
	m_worldMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 5.0f, m_pos.z);

	m_worldMat = tmpMat * m_worldMat;

	Math::Matrix mat = DirectX::XMMatrixTranslation(-2.0f, 0, 0);

	m_worldMat = mat * m_worldMat;

	return true;
}

void HPBar::Draw()
{
	if (m_enemy->GetAlive())
	{
		if (m_enemy->GetToPlayerDist() <= 20.0f)
		{
			//マップを被らないように深度テストをフォルスにする
			D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(false, false), 0);

			SHADER.m_effectShader.SetToDevice();

			UINT stride = sizeof(Vertex);
			UINT offset = 0;

			D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_emptyVb.GetAddress(), &stride, &offset);

			D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			D3D.GetDevContext()->PSSetShaderResources(0, 1, m_enemyHPEmpty->GetSRViewAddress());
			SHADER.m_effectShader.SetWorldMatrix(m_worldMat);
			SHADER.m_effectShader.WriteToCB();

			D3D.GetDevContext()->Draw(4, 0);


			D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_vb.GetAddress(), &stride, &offset);

			D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			D3D.GetDevContext()->PSSetShaderResources(0, 1, m_enemyHP->GetSRViewAddress());

			D3D.GetDevContext()->Draw(4, 0);

			D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
		}
	}
	
}





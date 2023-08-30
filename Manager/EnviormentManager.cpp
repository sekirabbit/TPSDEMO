#include"Headers.h"

EnviormentManager::EnviormentManager(GameScene* _gameScene)
{
	m_gameScene = _gameScene;

	m_skyDome = new SkyDome();
	m_ground = new Ground();
	m_river = new River();

	m_bridge = new Bridge(m_gameScene);
	m_bilud = new Bilud(m_gameScene);

	m_fences = new Fences(m_gameScene);
	m_bossDoor = new BossDoor(m_gameScene);

	m_hitMap = new HitMap();

	m_hitMapDrawFlg = false;

	//外部ファイルから木を初期設定して生成する
	for (auto i = 0; i < 290; i++)
	{
		FILE* fp;
		if (fopen_s(&fp, "Data/TreeData.csv", "r") == 0)
		{
			Math::Matrix mat;
			Math::Matrix rotMat;
			int No;
			Math::Vector3 pos;
			char dummy[256];
			for (int j = 0; j < i + 1; j++)
			{
				fgets(dummy, 256, fp);//一行読み込み
			}
			fscanf_s(fp, "%d,%f,%f,%f", &No, &pos.x, &pos.y, &pos.z);
			mat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
			rotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians((float)(rand() % 180)));
			mat = rotMat * mat;
			Tree* tree = new Tree(m_gameScene, mat);
			AddTree(tree);

			fclose(fp);
		}
	}

	m_swamp.clear();
}

EnviormentManager::~EnviormentManager()
{
	//map配置用
	//FILE* fp;
	//fopen_s(&fp, "Data/CreatTreeData.csv", "w");//w...write(新規作成) |r...read
	//fprintf(fp, "No,x,y,z\n");
	//for (UINT i = 0; i < m_tree.size(); i++)
	//{
	//	int No = i;
	//	Math::Vector3 pos = m_tree[i]->GetMat().Translation();
	//	fprintf(fp, "%d,%f,%f,%f\n", No, pos.x, pos.y, pos.z);
	//}
	//fclose(fp);

	delete m_skyDome;
	delete m_ground;
	delete m_river;
	delete m_fences;
	delete m_bilud;
	delete m_bridge;
	delete m_bossDoor;
	delete m_hitMap;

	for (auto i = 0; i < m_tree.size(); i++)
	{
		delete m_tree[i];
	}
	m_tree.clear();

	for (auto& obj : m_swamp)
	{
		delete obj;
	}
	m_swamp.clear();
}

void EnviormentManager::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	m_skyDome->Draw();
	m_ground->Draw();
	m_river->Draw();
	if (m_gameScene->GetEnemyManager().GetBossApear() == false)
	{
		m_fences->Draw();
		m_bilud->Draw();
		m_bridge->Draw();
	}
	if (m_hitMapDrawFlg == true)
	{
		m_hitMap->Draw();
	}
	for (auto i = 0; i < m_tree.size(); i++)
	{
		m_tree[i]->Draw();
	}

	for (auto& obj : m_swamp)
	{
		obj->Draw();
	}

}


void EnviormentManager::Update()
{
	m_skyDome->Update();
	m_bossDoor->Update();
	if (m_gameScene->GetEnemyManager().GetBossApear() == false)
	{
		for (auto i = 0; i < m_tree.size(); i++)
		{
			m_tree[i]->Update();
		}
	}

	auto it = m_swamp.begin();
	while (it != m_swamp.end())
	{
		if ((*it)->Update() == false)
		{
			delete(*it);
			it = m_swamp.erase(it);
		}
		else
		{
			++it;
		}
	}
	//法線のUVを操作
	static Math::Vector2 offset = { 0,0 };
	offset.x += 0.0001f;
	offset.y += 0.0001f;
	if (offset.x > 1)
	{
		offset.x -= 1;
	}
	if (offset.y > 1)
	{
		offset.y -= 1;
	}
	SHADER.m_standardShader.SetNormalUVOffset(offset);
}

void EnviormentManager::AddTree(Tree* _tree)
{
	m_tree.push_back(_tree);
}

void EnviormentManager::AddSwamp(Swamp* _swamp)
{
	m_swamp.push_back(_swamp);
}

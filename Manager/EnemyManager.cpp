#include"Headers.h"

EnemyManager::EnemyManager(GameScene* _gameScene)
{
	m_gameScene = _gameScene;

	//外部ファイルから敵を初期設定して生成する
	for (int i = 0; i < EnemySetting::outEnemyNum; i++)
	{
		FILE* fp;
		if (fopen_s(&fp, "Data/EnemyData.csv", "r") == 0)
		{
			Math::Matrix mat;
			Math::Matrix rotMat;
			int No;
			Math::Vector3 pos;
			float ang;
			int isSmoker;
			char dummy[256];
			for (int j = 0; j < i + 1; j++)
			{
				fgets(dummy, 256, fp);//一行読み込み
			}
			fscanf_s(fp, "%d,%f,%f,%f,%f,%d", &No, &pos.x, &pos.y, &pos.z, &ang, &isSmoker);
			mat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
			rotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(ang));
			mat = rotMat * mat;

			Enemy* enemy = new Enemy();
			enemy->SetOwner(m_gameScene);
			enemy->SetMat(mat);
			if (i == 5 || i == 10)
			{
				enemy->SetStateType(EnemyState::Awake);
			}
			//敵の種類を設定する
			if (isSmoker == 0)
			{
				enemy->SetEnemyType(EnemyType::Normal);
				KdModel* model = RESOURCE.GetModel("Data/Enemy/Zombie/Zombie_hitModel.gltf");
				enemy->SetHitModel(model);
				model = RESOURCE.GetModel("Data/Enemy/Zombie/Zombie_body.gltf");
				enemy->GetEnemyBody().SetModel(model);
			}
			else
			{
				enemy->SetEnemyType(EnemyType::Smoker);
				KdModel* model = RESOURCE.GetModel("Data/Enemy/Zombie/Smoker_hitModel.gltf");
				enemy->SetHitModel(model);
				model = RESOURCE.GetModel("Data/Enemy/Zombie/Smoker_body.gltf");
				enemy->GetEnemyBody().SetModel(model);
			}
			AddEnemy(enemy);
			fclose(fp);
		}
	}
	//事前Drawするためにbossのコンストラクタする
	Math::Vector3 bossBeginPos = BossSetting::beginPos;
	Math::Matrix mat = DirectX::XMMatrixTranslation(bossBeginPos.x, bossBeginPos.y, bossBeginPos.z);
	m_bossApearPos = mat.Translation();
	m_bossApearPos.y = 0;
	Math::Matrix rotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90));
	mat = rotMat * mat;
	m_boss = new BossEnemy(m_gameScene, mat);
	m_boss->SetMat(mat);
	m_bossApearFlg = false;
	m_clearFlg = false;
}

EnemyManager::~EnemyManager()
{
	for (auto i = 0; i < m_enemy.size(); i++)
	{
		delete m_enemy[i];
	}
	m_enemy.clear();

	delete m_boss;
}

void EnemyManager::Draw()
{
	if (m_bossApearFlg == false)
	{
		for (auto i = 0; i < m_enemy.size(); i++)
		{
			if (m_enemy[i]->GetAlive() || m_enemy[i]->GetDieMotionFlg())
			{
				m_enemy[i]->Draw();
			}

		}
	}

	if (m_boss->GetAlive() || m_boss->GetDieMotionFlg())
	{
		m_boss->Draw();
	}

	for (auto i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->GetHPBar().Draw();
	}

}

void EnemyManager::Update()
{
	if (m_bossApearFlg == false)
	{
		Math::Vector3 playerPos = m_gameScene->GetPlayerManager().GetPlayer().GetPos();
		//ノーマル敵の更新
		for (auto i = 0; i < m_enemy.size(); i++)
		{
			m_enemy[i]->Update();
		}
	}

	//boss敵の更新
	m_boss->Update();
}

void EnemyManager::AddEnemy(Enemy* _enemy)
{
	m_enemy.push_back(_enemy);
}



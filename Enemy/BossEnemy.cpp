#include "Headers.h"

BossEnemy::BossEnemy(GameScene* _gameScene, const Math::Matrix& _mat)
{
	m_gameScene = _gameScene;

	m_model = RESOURCE.GetModel("Data/Enemy/BossNoHands.gltf");

	m_aliveFlg = false;
	m_enemyType = EnemyType::Boss;
	m_stateType = EnemyState::Nova;

	m_worldMat = _mat;
	m_vomit = new Vomit(m_gameScene, this, m_worldMat, Math::Vector3::Zero);

	m_hpMax = BossSetting::maxHp;
	m_hp = m_hpMax;
	m_breakHPMax = BossSetting::breakHP;
	m_breakHP = m_breakHPMax;

	m_dieMotionFlg = false;
	m_dissolvePow = 0;
	//ノーマル敵のディゾルブ処理後んの初期化設定
	SHADER.m_standardShader.SetDissolvePower(0);
	//一定のHP以下になったら、狂暴化する
	m_angryFlg = false;
	m_apearMotionTime = BossSetting::apearMotionTime;
	m_currentState = nullptr;

}

void BossEnemy::Update()
{
	if (m_gameScene->GetEnemyManager().GetBossApear())
	{
		ApearMotion();
	}
	if (m_aliveFlg == true)
	{
		if (m_hp <= 0)
		{
			m_aliveFlg = false;
			m_dieMotionFlg = true;
			SHADER.m_standardShader.SetDissolvePower(0);
		}
		if (m_hp <= (m_hpMax / 2))
		{
			SetAngry(true);
			SHADER.m_standardShader.SetDissolvePower(0);
			//毒フーグになる
			SHADER.m_cb7_Camera.Work().DistanceFogColor = { 0.5f,0.7f,0.5f };//フォグの色（RGB）
		}


		

		if (m_currentState != nullptr)
		{
			BaseState* nextState;
			//ワールド軸で行動を更新する
			nextState = m_currentState->Action(this, m_gameScene);

			//別のステートへの移行希望が帰ってきた
			if (nextState != nullptr)
			{
				//現在のステートを削除
				delete m_currentState;
				//移行先を現在のステートとする
				m_currentState = nextState;
			}
		}
		//AI実行以後のm_posを更新
		m_pos = m_worldMat.Translation();
		//AIでワールド座標を変更した以後の回転角度を求める
		m_ang = GetVecAngY(DirectX::XMVector3TransformNormal(Math::Vector3{ 0,0,1 }, m_worldMat));
		HitAbout();
	}
	else
	{
		if (m_dieMotionFlg == true)
		{
			DieMotion();
		}
	}

}

void BossEnemy::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	if (m_stateType == EnemyState::Weak)
	{
		for (auto dizzy : m_dizzy)
		{
			dizzy->Draw();
		}
	}
	if (m_dieMotionFlg)
	{
		SHADER.m_standardShader.SetDissolveEnable(true);
	}
	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 1.0f,0.2f,0.2f });
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetDitherEnable(true);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetDissolveEnable(false);
	SHADER.m_standardShader.SetLimLightEnable(false);

	if (m_stateType == EnemyState::Nova)
	{
		m_vomit->NovaModelDraw();
	}
}

void BossEnemy::ApearMotion()
{
	m_aliveFlg = true;
	m_apearMotionTime--;

	Math::Vector3 moveVec = Math::Vector3{ 0,0.1f,0.01f };

	Math::Matrix mat = DirectX::XMMatrixTranslation(0, moveVec.y, moveVec.z);
	
	m_worldMat = mat * m_worldMat;

	if (m_apearMotionTime <= 0)
	{
		m_apearMotionTime = 0;
		m_currentState = new Track();
	}
}

BossEnemy::~BossEnemy()
{
	if (m_currentState != nullptr)
	{
		delete m_currentState;
	}
	delete m_vomit;

	for (auto dizzy : m_dizzy)
	{
		delete dizzy;
	}
	m_dizzy.clear();
}

bool BossEnemy::CheckEnemy(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec) const
{
	if (ModelIntersects(*m_model, m_worldMat, _rayPos, _rayVec, _dis, _normalVec))
	{
		return true;
	}
	return false;
}
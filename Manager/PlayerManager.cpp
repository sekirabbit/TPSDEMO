#include"Headers.h"

void PlayerManager::DynamicDraw()
{
	//ブライト専用ドロー
	SHADER.m_standardShader.SetToDevice();
	m_sword->Draw();
}

void PlayerManager::Update()
{
		//体
		m_player->Update(m_gameScene->GetCamera().GetCameraAngY());
		m_playerBody->Update();
		m_playerHead->Update();
		m_playerLeftShoulder->Update();
		m_playerRightShoulder->Update();
		m_playerLeftArm->Update();
		m_playerRightArm->Update();
		m_playerLeftHand->Update();
		m_playerRightHand->Update();
		m_playerLeftLeg->Update();
		m_playerRightLeg->Update();
		m_playerLeftFoot->Update();
		m_playerRightFoot->Update();
		//装備
		m_hat->Update();
		m_sword->Update();
		m_gunHandle->Update();
		m_gunBarrel->Update();
	

}

void PlayerManager::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetNormalEnable(false);

	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 0.2f,0.2f,1.0f });


	//体
	m_playerHead->Draw();
	m_playerBody->Draw();
	m_playerLeftShoulder->Draw();
	m_playerRightShoulder->Draw();
	m_playerLeftArm->Draw();
	m_playerRightArm->Draw();
	m_playerLeftHand->Draw();
	m_playerRightHand->Draw();
	m_playerLeftFoot->Draw();
	m_playerRightFoot->Draw();
	m_playerLeftLeg->Draw();
	m_playerRightLeg->Draw();
	//装備
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 5.0f,0.5f,0.5f });
	SHADER.m_standardShader.SetLimLightRate(5.0f);
	m_sword->Draw();
	m_gunHandle->Draw();
	m_gunBarrel->Draw();
	m_hat->Draw();

	SHADER.m_standardShader.SetLimLightEnable(false);

}

PlayerManager::PlayerManager(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	//体
	m_player = new Player(m_gameScene);
	m_playerBody = new Player_body(m_gameScene);
	m_playerHead = new Player_head(m_gameScene);
	m_playerLeftShoulder = new Player_leftShoulder(m_gameScene);
	m_playerRightShoulder = new Player_rightShoulder(m_gameScene);
	m_playerLeftArm = new Player_leftArm(m_gameScene);
	m_playerRightArm = new Player_rightArm(m_gameScene);
	m_playerLeftHand = new Player_leftHand(m_gameScene);
	m_playerRightHand = new Player_rightHand(m_gameScene);
	m_playerLeftLeg = new Player_leftLeg(m_gameScene);
	m_playerRightLeg = new Player_rightLeg(m_gameScene);
	m_playerLeftFoot = new Player_leftFoot(m_gameScene);
	m_playerRightFoot = new Player_rightFoot(m_gameScene);
	//装備
	m_hat = new Hat(m_gameScene);
	m_sword = new Sword(m_gameScene);
	m_gunHandle = new GunHandle(m_gameScene);
	m_gunBarrel = new GunBarrel(m_gameScene);
}

PlayerManager::~PlayerManager()
{
	delete m_player;
	delete m_playerBody;
	delete m_playerHead;
	delete m_playerLeftShoulder;
	delete m_playerRightShoulder;
	delete m_playerLeftArm;
	delete m_playerRightArm;
	delete m_playerLeftHand;
	delete m_playerRightHand;
	delete m_playerLeftLeg;
	delete m_playerRightLeg;
	delete m_playerLeftFoot;
	delete m_playerRightFoot;
	delete m_hat;
	delete m_sword;
	delete m_gunHandle;
	delete m_gunBarrel;

}
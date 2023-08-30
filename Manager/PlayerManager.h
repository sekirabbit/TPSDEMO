#pragma once

class GameScene;

class Player;
class Player_head;
class Player_body;
class Player_leftShoulder;
class Player_rightShoulder;
class Player_leftArm;
class Player_rightArm;
class Player_leftHand;
class Player_rightHand;
class Player_lowerBody;
class Player_leftFoot;
class Player_rightFoot;
class Player_leftLeg;
class Player_rightLeg;
class Hat;
class Sword;
class GunHandle;
class GunBarrel;

class PlayerManager
{
public:
	PlayerManager(GameScene* _gameScene);
	~PlayerManager();
	
	void Update();
	void DynamicDraw();
	void Draw();

	Player& GetPlayer()
	{
		return *m_player;
	}
	Player_head& GetPlayerHead()
	{
		return *m_playerHead;
	}
	Player_body& GetPlayerBody()
	{
		return *m_playerBody;
	}
	Player_leftShoulder& GetPlayerLShoulder()
	{
		return *m_playerLeftShoulder;
	}
	Player_rightShoulder& GetPlayerRShoulder()
	{
		return *m_playerRightShoulder;
	}
	Player_leftArm& GetPlayerLArm()
	{
		return *m_playerLeftArm;
	}
	Player_rightArm& GetPlayerRArm()
	{
		return *m_playerRightArm;
	}
	Player_leftHand& GetPlayerLHand()
	{
		return *m_playerLeftHand;
	}
	Player_rightHand& GetPlayerRHand()
	{
		return *m_playerRightHand;
	}
	Player_leftFoot& GetPlayerLFoot()
	{
		return *m_playerLeftFoot;
	}
	Player_rightFoot& GetPlayerRFoot()
	{
		return *m_playerRightFoot;
	}
	Player_leftLeg& GetPlayerLLeg()
	{
		return *m_playerLeftLeg;
	}
	Player_rightLeg& GetPlayerRLeg()
	{
		return *m_playerRightLeg;
	}
	Hat& GetHat()
	{
		return *m_hat;
	}
	Sword& GetSword()
	{
		return *m_sword;
	}
	GunHandle& GetGunHandle()
	{
		return *m_gunHandle;
	}
	GunBarrel& GetGunBarrel()
	{
		return *m_gunBarrel;
	}

private:
	GameScene* m_gameScene;

	Player* m_player;
	Player_head* m_playerHead;
	Player_body* m_playerBody;
	Player_leftShoulder* m_playerLeftShoulder;
	Player_rightShoulder* m_playerRightShoulder;
	Player_leftArm* m_playerLeftArm;
	Player_rightArm* m_playerRightArm;
	Player_leftHand* m_playerLeftHand;
	Player_rightHand* m_playerRightHand;
	Player_lowerBody* m_playerLowerBody;
	Player_leftFoot* m_playerLeftFoot;
	Player_rightFoot* m_playerRightFoot;
	Player_leftLeg* m_playerLeftLeg;
	Player_rightLeg* m_playerRightLeg;
	Hat* m_hat;
	Sword* m_sword;
	GunHandle* m_gunHandle;
	GunBarrel* m_gunBarrel;
};
#include"Headers.h"

Camera::Camera(GameScene* _gameScene)
{
	m_gameScene = _gameScene;

	//マオス関係

	// ゲーム画面の中央(クライアント座標)
	m_basePt.x = ScrW / 2;
	m_basePt.y = ScrH / 2;
	ClientToScreen(APP.m_window.GetWndHandle(), &m_basePt);
	SetCursorPos(m_basePt.x, m_basePt.y);
	ShowCursor(false);

	//カメラ情報
	m_cameraAngX = 0;
	m_cameraAngY = 0;
	m_worldMat = DirectX::XMMatrixIdentity();
	m_camPos = {};
	m_camLock = {};
	m_playerCamPos = {};
	m_playerCamLock = {};
	m_moveStartPos = {};
	m_moveEndPos = {};
	m_camHead = Math::Vector3(0, 1, 0);
	m_settingVec = { 0,3,-5 };
	m_cameraTurnAng = 5.0f;

	m_moveFlg = false;
	m_moveRound = 0;
	m_moveSpeed = 0.1f;

}

void Camera::Update()
{
	//IMGUIを使用するため、マオスを不使用
	if (m_gameScene->GetImGuiFlg() == false && m_gameScene->GetMenuOpen() == false && m_gameScene->GetEnemyManager().GetBossApear() == false)
	{
		POINT currentPt;
		GetCursorPos(&currentPt);

		m_cameraAngY += (currentPt.x - m_basePt.x) / 8.0f;
		m_cameraAngX += (currentPt.y - m_basePt.y) / 8.0f * 1;


		SetCursorPos(m_basePt.x, m_basePt.y);
	}

	//カメラ情報の設定
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();

	Math::Vector3 currentCamPos;
	Math::Vector3 currentCamLock;

	m_playerCamLock = DirectX::XMVector3TransformCoord(Math::Vector3(0, 6.5f, 0), playerMan.GetPlayer().GetMat());
	m_playerCamPos = MoveVec(m_cameraAngY, m_settingVec);
	m_playerCamPos += m_playerCamLock;

	//Boss出現時にカメラの動き
	if (m_moveFlg)
	{
		//変更初期設定（座標、ベクトル、スビートなど）
		float rate = 0.03f;
		float movePow = 0.03f; 
		
		currentCamPos = m_camPos;
		currentCamLock = m_camLock;

		Math::Vector3 posVec = m_moveEndPos - currentCamPos;
		Math::Vector3 lockVec = m_moveEndLock - currentCamLock;
		float posLength = posVec.Length();

		if ((m_moveSpeed >= posLength) || (posLength <= 0.2f))
		{
			//End地点に到着したらEndとStart切り替え（camPos,camLockとも）
			currentCamPos = m_moveEndPos;
			currentCamLock = m_moveEndLock;

			Math::Vector3 tmpVec = m_moveEndPos;
			m_moveEndPos = m_playerCamPos;
			m_moveStartPos = tmpVec;

			tmpVec = m_moveEndLock;
			m_moveEndLock = m_playerCamLock;
			m_moveStartLock = tmpVec;

			m_moveSpeed = 0;
			m_moveRound++;
		}
		else
		{
			if (posLength < 50)
			{
				m_moveSpeed = posLength * rate;
			}
			else
			{
				m_moveSpeed = 0.1f;
			}
			posVec.Normalize();
			Math::Vector3 posMoveVec = posVec * m_moveSpeed;
			currentCamPos += posMoveVec;

			lockVec.Normalize();
			Math::Vector3 lockMoveVec = lockVec * m_moveSpeed;
			currentCamLock += lockMoveVec;
		}
		//カメラの移動終わったらフラグ変更して操作できる
		if (m_moveRound == 2)
		{
			m_moveFlg = false;
			m_gameScene->GetEnemyManager().SetBossApear(false);
		}
	}
	else
	{
		currentCamPos = m_playerCamPos;
		currentCamLock = m_playerCamLock;
	}
	m_camPos = currentCamPos;
	m_camLock = currentCamLock;

}


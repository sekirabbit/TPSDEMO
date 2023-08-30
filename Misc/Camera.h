#pragma once

class GameScene;

class Camera
{
public:
	Camera(GameScene* _gameScene);
	void Update();

	void SetCamMovePos(const Math::Vector3& _startPos, const Math::Vector3& _endPos)
	{
		m_moveStartPos = _startPos;
		m_moveEndPos = _endPos;
	}

	void SetCamMoveLock(const Math::Vector3& _startLock, const Math::Vector3& _endLock)
	{
		m_moveStartLock = _startLock;
		m_moveEndLock = _endLock;
	}

	const float& GetCameraAngY()const
	{
		return m_cameraAngY;
	}

	const Math::Vector3& GetCameraPos()const
	{
		return m_camPos;
	}
	void AddCamPos(const Math::Vector3& _vec)
	{
		m_camPos += _vec;
	}
	void SetCamPos(const Math::Vector3& _vec)
	{
		m_camPos = _vec;
	}

	const Math::Vector3& GetCameraLock()const
	{
		return m_camLock;
	}

	const Math::Vector3& GetCameraHead()const
	{
		return m_camHead;
	}
	
	const bool GetMoveFlg() const
	{
		return m_moveFlg;
	}
	void SetMoveFlg(bool _flg)
	{
		m_moveFlg = _flg;
	}

private:
	GameScene* m_gameScene;
	POINT m_basePt;
	Math::Matrix m_worldMat;
	Math::Vector3 m_settingVec;
	Math::Vector3 m_camPos;
	Math::Vector3 m_playerCamPos;
	Math::Vector3 m_playerCamLock;
	Math::Vector3 m_moveStartPos;
	Math::Vector3 m_moveEndPos;
	Math::Vector3 m_moveStartLock;
	Math::Vector3 m_moveEndLock;
	Math::Vector3 m_camLock;
	Math::Vector3 m_camHead;
	float m_cameraAngX;
	float m_cameraAngY;
	float m_cameraTurnAng;

	bool m_moveFlg;

	int m_moveRound;
	float m_moveSpeed;
	float m_distance; //‘S‘Ì‚Ì‹——£

};
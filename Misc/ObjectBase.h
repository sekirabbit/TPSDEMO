#pragma once

//基底クラス(親クラス)
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	//仮想関数にしておく
	virtual void Update();
	virtual void Draw();
	void PosToMat();
	void HitObj(ObjName _obj, GameScene* _gameScene, const Math::Vector3& _rayVec = Math::Vector3{0,0,0});
	bool CheckModel(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec)const;
	bool FallDown(GameScene* _gameScene);
	const ObjType& GetObjType()const
	{
		return m_objType;
	}
	const Math::Vector3& GetPos()const
	{
		return m_pos;
	}
	const Math::Matrix& GetMat()const
	{
		return m_worldMat;
	}
	const bool GetAlive()const
	{
		return m_aliveFlg;
	}
	const float& GetAng()const
	{
		return m_ang;
	}
	void SetPos(const Math::Vector3& _pos)
	{
		m_pos = _pos;
	}
	virtual void AddPos(const Math::Vector3& _pos)
	{
		m_pos += _pos;
	}
	void SetMat(const Math::Matrix& _mat)
	{
		m_worldMat = _mat;
	}
	void MultMat(const Math::Matrix& _mat)
	{
		m_worldMat = _mat * m_worldMat;
	}
	void AddMat(const Math::Matrix& _mat)
	{
		m_worldMat._41 += _mat._41;
		m_worldMat._42 += _mat._42;
		m_worldMat._43 += _mat._43;
	}
	Math::Vector3 GetFrontVec(const Math::Matrix& _mat)
	{
		Math::Vector3 frontVec;
		frontVec = DirectX::XMVector3TransformNormal(Math::Vector3{ 0,0,1 }, _mat);
		return frontVec;
	}
protected:
	GameScene* m_gameScene;
	KdModel* m_model;
	ObjType m_objType;

	bool m_aliveFlg;
	Math::Matrix m_worldMat;
	Math::Vector3 m_pos;
	float m_ang;
	Math::Vector3 m_moveVec;

	Math::Matrix m_localMat;

	Math::Matrix m_startMat;
	Math::Matrix m_endMat;

	bool m_animeFlg;
	float m_animeFrame;
	float m_turnAng;
	float m_addTime;
};

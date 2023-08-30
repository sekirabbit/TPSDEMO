#pragma once

//���N���X(�e�N���X)
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	//���z�֐��ɂ��Ă���
	virtual bool Update();
	virtual void Draw();
	const Math::Vector3& GetPos()const
	{
		return m_pos;
	}
	const Math::Matrix& GetMat()const
	{
		return m_worldMat;
	}
	void AddPos(const Math::Vector3& _pos)
	{
		m_pos += _pos;
	}
	void SetMat(const Math::Matrix& _mat)
	{
		m_worldMat = _mat;
	}


	const float& GetSize()
	{
		return m_size;
	}
	void SetSize(const float& _size)
	{
		m_size = _size;
	}
protected:
	GameScene* m_gameScene;
	KdModel* m_model;
	KdTexture* m_tex;

	Math::Matrix m_worldMat;
	Math::Vector3 m_pos;

	float m_size;
	float m_alpha;
	// �u�����h�X�e�[�g
	ID3D11BlendState* m_blendAlpha;
	ID3D11BlendState* m_blendAdd;
};

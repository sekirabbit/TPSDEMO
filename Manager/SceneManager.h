#pragma once

class SceneManager
{
public:

	~SceneManager();

	void DoScene();
	void ChangeScene(BaseScene* _nextScene);

	//�V���O���g��
	//�ЂƂ@down
	//������

	//���̂�錾���ĕԂ� (�֐���)
	static SceneManager& GetInstance()
	{
		static SceneManager sceneManager;

		return sceneManager;
	}

private:
	//�V���O���g���̓����Ƃ�
	//�R���X�g���N�^�̈ʒu��private�ɂ���
	SceneManager()
	{
	}

	//�p���֌W�̒��Ɉ�ԔN��̃N���X��(BaseScene=���N���X)
	BaseScene* m_currentScene = nullptr;//���ݎ��s���̃V�[��
	BaseScene* m_nextScene = nullptr;//���Ɏ��s�������̃V�[��

	//State(�X�e�[�g)�p�^�[��
	//�f�U�C���p�^�[���̂ЂƂ�
	//�����Ԃ�\���N���X���X�ɍ��
	//�����݂̏�Ԃ�\���N���X�����悤�ɂ���

};

//�}�N��(���O�ɐݒ芮���̖���)���쐬
#define SCENEMANAGER SceneManager::GetInstance()

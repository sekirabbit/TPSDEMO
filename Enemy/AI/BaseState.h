#pragma once

class GameScene;
class Enemy;

class BaseState
{
public:
	virtual BaseState* Action(Enemy* _enemy, GameScene* _gameScene) = 0;
	//�������z�֐� =>�@�p�������h���N���X����
	//���̊֐����I�[�o�[���C�h���Ȃ���΂Ȃ�Ȃ�
};
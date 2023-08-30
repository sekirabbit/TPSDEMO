#pragma once

#include"main.h"
#include"define.h"
#include "Manager/ResourceManager.h"

Math::Vector3 GetDot(const Math::Vector3& _rayVec, const Math::Vector3& _normal);
bool ModelIntersects(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec);
float GetVecAngY(const Math::Vector3& _vec);
float TurnToAng(Math::Matrix& _mat, const float _targetAng, const float _plusAng);
Math::Vector3 MoveVec(const float& _ang, const Math::Vector3& _vec);
Math::Vector3 GetLookVec(const float& _angX, const float& _angY);
Math::Vector3 GetNormal(Math::Matrix& _mat);
void AnimeProc(Math::Matrix& _startMat, Math::Matrix& _endMat, const float _animeFrame, Math::Matrix& _mat);
bool AttackCheck(Math::Vector3 _attackVec, Math::Vector3 _damageVec, float _hitDis);

#include"System.h"
#include"config.h"

#include"Sound.h"

#include"BaseState.h"
#include"Awake.h"
#include"Stay.h"
#include"WalkAround.h"
#include"AttackWait.h"
#include"DashAttack.h"
#include"BossDashAttack.h"
#include"VomitAttack.h"
#include"BossVomitAttack.h"
#include"DrugNova.h"
#include"Track.h"
#include"BossAngry.h"
#include"Weak.h"

#include"BuffBase.h"
#include"Drug.h"
#include"Bleed.h"
#include"Heal.h"
#include"BuffManager.h"


#include"ObjectBase.h"
#include"HitMap.h"
#include"SkyDome.h"
#include"Ground.h"
#include"River.h"
#include"Tree.h"
#include"Fences.h"
#include"Bilud.h"
#include"Bridge.h"
#include"BossDoor.h"
#include"Swamp.h"
#include"EnviormentManager.h"

#include"Hat.h"
#include"Sword.h"
#include"GunHandle.h"
#include"GunBarrel.h"
#include"Bullet.h"

#include"ItemBase.h"
#include"Potion.h"
#include"Ammo.h"
#include"ItemManager.h"

#include"Player_body.h"
#include"Player_head.h"
#include"Player_leftShoulder.h"
#include"Player_rightShoulder.h"
#include"Player_leftArm.h"
#include"Player_rightArm.h"
#include"Player_leftHand.h"
#include"Player_rightHand.h"
#include"Player_leftFoot.h"
#include"Player_rightFoot.h"
#include"Player_leftLeg.h"
#include"Player_rightLeg.h"
#include"Player.h"
#include"PlayerManager.h"

#include"Camera.h"

#include"Vomit.h"
#include"Dizzy.h"
#include"Enemy_hand.h"
#include"Enemy_body.h"
#include"Enemy_leftLeg.h"
#include"Enemy_rightLeg.h"
#include"BossEnemy.h"
#include"EnemyManager.h"

#include"EffectBase.h"
#include"Smoke.h"
#include"Slash.h"
#include"Fire.h"
#include"Explode.h"
#include"Blood.h"
#include"PointBlood.h"
#include"DamageNum.h"
#include"HPBar.h"
#include"Attention.h"
#include"EffectManager.h"

#include"UI.h"

#include"BaseScene.h"
#include"TitleScene.h"
#include"GameOverScene.h"
#include"GameClearScene.h"
#include"GameScene.h"
#include"SceneManager.h"




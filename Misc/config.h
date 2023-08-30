#pragma once
//map関係の当たり判定の相手
enum class ObjName
{
	HitMap,
	Ground,
	Swamp,
	River,
	Bridge,
};
//プレイヤーの動作状態
enum class PlayerState
{
	Null,
	Stay,
	Move,
	Slash1,
	Slash2,
	SlashWait1,
	SlashWait2,
	Fire,
	Reload,
};
//アイテムの種類
enum class ItemType
{
	Potion,
	Ammo,
};

//buffを持つ対象を判別
enum class ObjType
{
	Player,
	Enemy,
};
//buffの種類
enum class BuffName
{
	Null,
	//DeBuff
	Bleed,
	Drug,
	Heal,
};
//敵の種類
enum class EnemyType
{
	Normal,
	Smoker,
	Boss,
};
//敵の攻撃種類
enum class EnemyAttackType
{
	Close,
	Far,
};
//敵の動作状態
enum class EnemyState
{
	Walk,
	Awake,
	Angry,
	Stay,
	Track,
	AttackWait,
	Attack,
	VomitAttack,
	Nova,
	Weak,
};
class PlayerSetting
{
public:
	static constexpr float maxSpeed = 0.25f;
	//加速度
	static constexpr float acceleration = 0.01f;
	static constexpr float maxHp = 200.0f;
	static constexpr float blurTime = 70.0f;
	//一撃後の待ち時間時間
	static constexpr float slashWaitTime = 20.0f;
	//斬撃中の移動量
	static constexpr float slashMovePow = 0.05f;
	static constexpr float hitWaitTime = 30.0f;
	static constexpr int takeBulletNum = 12;
	static constexpr int fireEnableBulletNum = 2;
	static constexpr int takePotionMaxNum = 3;
	//回復ポーションを使うための待ち時間(healBuffTime * 2)
	static constexpr float usePotionWaitTime = 120.0f;
};

class EquitSetting
{
public:
	static constexpr float swordDamage = -40.0f;
	static constexpr float slashBackPow = 0.2f;
	static constexpr float gunDamage = -15.0f;
	static constexpr int outBulletNum = 10;
	static constexpr float shotBackPow = 1.5f;
	static constexpr float bulletWidth = 0.1f;
	static constexpr float bulletLength = 20.0f;
	static constexpr float bulletAlpha = 1.0f;
	static constexpr float bulletSpeed = 1.0f;
	static constexpr int bulletCountTime = 10;
	static constexpr float bulletHitEnableDis = 15.0f;
	static constexpr float potionHealPower = 100.0f;


	static constexpr float weakAttackRate = 1.3f;
};

class EnemySetting
{
public:
	static constexpr int outEnemyNum = 12;

	static constexpr float maxHp = 200.0f;
	static constexpr float breakHP = 120.0f;
	static constexpr int weakTime = 180;
	static constexpr float speed = 0.02f;
	//Stayステート中近すぎると注意される距離
	static constexpr float awakeDis = 4.0f;
	//AttackWaitステートのlifeTime
	static constexpr float attackWaitTime = 80;
	//ダメージを受けすぎ防止
	static constexpr int hitWaitTime = 30;
	static constexpr float attackSpeedAcceleration = 0.05f;
	static constexpr float attackMaxSpeed = 0.35f;
	static constexpr float turnAng = 1.0f;
	static constexpr float searchingRange = 20.0f;
	static constexpr float searchingAng = 30.0f;
	static constexpr float focuSpeed = 0.05f;
	static constexpr float focuTurnAng = 5.0f;
	static constexpr float smokerFocuTurnAng = 2.5f;
	//この範囲内に攻撃関係ステートに変更する
	static constexpr float normalAttackStartDis = 4.0f;
	static constexpr float smokerAttackStartDis = 10.0f;
	static constexpr float attackPower = -5.0f;
	static constexpr float attackBackPower = 0.5f;
	static constexpr float attackMoveDis = 5.0f;
	//プレーヤーとの当たり判定距離
	static constexpr float attackRange = 2.0f;
	static constexpr float vomitPower = -5.0f;
	static constexpr float vomitBackPower = 0.5f;
	static constexpr float vomitHitEnableDis = 2.0f;
	static constexpr float vomitSpeed = 0.3f;
	static constexpr float vomitGravity = 0.01f;
	//重ねる防止距離
	static constexpr float toPlayerLimitDis = 2.0f;
	static constexpr float toEnemyLimitDis = 2.0f;

};


class BossSetting
{
public:
	static constexpr Math::Vector3 beginPos = Math::Vector3(-196.0f, -7.0f, 178.0f);

	static constexpr float speed = 0.2f;
	static constexpr float maxHp = 2500.0f;
	static constexpr float breakHP = 500.0f;
	static constexpr float searchingRange = 100.0f;
	//この範囲内に攻撃関係ステートに変更する
	static constexpr float attackPower = -10.0f;
	static constexpr float attackStartDis = 15.0f;
	static constexpr float attackBackPower = 1.5f;
	static constexpr float attackSpeedAcceleration = 0.02f;
	static constexpr float angryAcceleration = 0.04f;
	static constexpr float attackMaxSpeed = 0.7f;
	//
	static constexpr float attackMoveDis = 20.0f;
	//プレーヤーとの当たり判定距離
	static constexpr float attackRange = 5.0f;
	//BossはskillUsePossible分の1の可能性でskillを使う
	static constexpr int skillUsePossible = 10;
	static constexpr int vomitNum = 4;
	static constexpr float vomitSpeed = 0.5f;
	static constexpr float angryVomitSpeed = 0.8f;
	static constexpr float vomitOutWaitTime = 10.0f;

	static constexpr float novaPower = -20.0f;
	static constexpr float novaBaseSize = 5.5f;
	static constexpr float novaBigestSize = 7.5f;

	//重ねる防止距離
	static constexpr float toPlayerLimitDis = 4.3f;

	//モーション関係
	static constexpr float apearMotionTime = 200.0f;
	static constexpr Math::Vector3 makeBossApearPos = Math::Vector3(-151.0f, 7.0f, 171.5f);
	
};

class EffectSetting
{
public:
	static constexpr float bloodSize = 0.05f;
	static constexpr float bloodLifeTime = 30.0f;
};

class BuffSetting
{
public:
	static constexpr float drugLifeTime = 120.0f;
	static constexpr float drugDamage = -0.1f;
	static constexpr float bleedLifeTime = 60.0f;
	static constexpr float bleedDamage = -0.2f;
	static constexpr float healLifeTime = 60.0f;
};

class MapSetting
{
public:
	//接近できる限界距離
	static constexpr float playerAwayDistance = 1.5f;	
	static constexpr float playerAwayTreeDistance = 2.5f;
	static constexpr float voimitAwayDistance = 0.5f;	


};
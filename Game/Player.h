#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"
#include "Benelli_M4.h"
#include "M4A1.h"
#include "MP5.h"
#include "M110.h"
#include "SMAW.h"
#include "Physics/CollisionAttr.h"
#include "WeaponAttr.h"

class GameCamera;
struct SPlayerStatus
{
	int HitPoint = 100;				//体力
	int Kills = 0;					//キル数
	int HealTimer = 0;				//自動回復するまでの時間
};
class Player
{
public:
	
	Player(int playerNo);
	~Player();
	void Update(Camera& camera, int PlayerNumber);
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	CVector3 GetMoveSpped()
	{
		return m_moveSpeed;
	}
	CVector3 GetForward()
	{
		return m_forward;
	}
	CVector3 GetRight()
	{
		return m_right;
	}
	float GetRStickX()
	{
		return m_rStickX;
	}
	float GetRStickY()
	{
		return m_rStickY;
	}
	float GetLStickX()
	{
		return m_lStickX;
	}
	float GetLStickY()
	{
		return m_lStickY;
	}
	CVector3 GetHandPos()
	{
		return m_RhandPos;
	}
	SPlayerStatus GetStatus()
	{
		return m_status;
	}
	void SetHitPoint(int hp)
	{
		m_status.HitPoint = hp;
	}
	void SetDead()
	{
		m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Ground);

		m_state = enState_Death;
	}
	void SetKills(int kills)
	{
		m_status.Kills = kills;
	}
	void SetHealTimer(int timer)
	{
		m_status.HealTimer = timer;
	}
	void SetCameraDirection(CVector3 direction)
	{
		m_cameraDirection = direction;
	}
	void DrawSetFalse()
	{
		m_drawflag = false;
	}
	void DrawSetTrue()
	{
		m_drawflag = true;
	}
	
private:
	enum EnCameraType {
		enType_TPS,
		enType_FPS
	};
	void Shot(int PlayerNumber,Camera& camera);
public:
	bool GetCameraType()
	{
		return m_cameratype;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	SkinModel GetSkinModel()
	{
		return m_model;
	}
	bool GetCrouch()
	{
		return m_crouch;
	}
	int GetRandom(int min, int max)
	{
		return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
	}
	int GetKills()
	{
		return m_status.Kills;
	}
	bool GetDrawFlag()
	{
		return m_drawflag;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	int GetHitPoint()
	{
		return m_status.HitPoint;
	}
	void SetAttackTrue()
	{
		m_attackflag = true;
	}
	void SetAttackFalse()
	{
		m_attackflag = false;
	}
	void SetAttackCount(int time)
	{
		m_attackflagcount = time;
	}
	bool GetAttackFlag()
	{
		return m_attackflag;
	}
	void SetKillTrue()
	{
		m_killflag = true;
	}
	void SetKillFalse()
	{
		m_killflag = false;
	}
	void SetKillCount(int time)
	{
		m_killflagcount = time;
	}
	bool GetKillFlag()
	{
		return m_killflag;
	}
	EnWeapon GetWeapon()
	{
		return m_weapon;
	}
	void SetWeaponInstance(M4A1 *m4a1,MP5 *mp5,Benelli_M4 *benelliM4,M110 *m110)
	{
		m_m4a1 = m4a1;
		m_mp5  = mp5;
		m_benelliM4 = benelliM4;
		m_m110 = m110;
	}
private:
	void InitAnimation();								//アニメーションの初期化
	void Move(Camera& camera, int PlayerNumber);					//移動処理
	void Turn(int PlayerNumber);									//回転処理
	enum EnAnimation {
		enAnimation_Idle,
		enAnimation_Walk_Forward,
		enAnimation_Walk_Back,
		enAnimation_Walk_Right,
		enAnimation_Walk_Left,
		enAnimation_Walk_Shoot,
		enAnimation_Walk_Reload,
		enAnimation_Run,
		enAnimation_Jump_Start,
		enAnimation_Jump_Air,
		enAnimation_Jump_Land,
		enAnimation_Crouch_Idle,
		enAnimation_Crouch_Reload,
		enAnimation_Crouch_Shoot,
		enAnimation_Crouch_Walk_Shoot,
		enAnimation_Crouch_Walk_Forward,
		enAnimation_Reload,
		enAnimation_Shoot,
		enAnimation_Damage,
		enAnimation_Death,
		enAnimation_Grenade,
		enAnimation_Num
	};
	enum EnState {
		enState_Idle,
		enState_Walk_Forward,
		enState_Walk_Back,
		enState_Walk_Right,
		enState_Walk_Left,
		enState_Walk_Shoot,
		enState_Walk_Reload,
		enState_Run,
		enState_Jump_Start,
		enState_Jump_Air,
		enState_Jump_Land,
		enState_Crouch_Idle,
		enState_Crouch_Reload,
		enState_Crouch_Shoot,
		enState_Crouch_Walk_Shoot,
		enState_Crouch_Walk_Forward,
		enState_Reload,
		enState_Shoot,
		enState_Damage,
		enState_Death,
		enState_Grenade,
		enState_Num
	};
	SkinModel m_model;									//スキンモデル。
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[enAnimation_Num];	//アニメーションクリップ。
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_scale = CVector3::One();					//拡大率。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	CVector3 m_forward;									//キャラクターの前方向
	CVector3 m_right;									//キャラクターの右方向
	CharacterController m_charaCon;						//キャラクターコントローラー
	EnState m_state = enState_Idle;						//状態
	bool m_cameratype = EnCameraType::enType_TPS;		//カメラ
	float m_rStickX;									//右スティックのX
	float m_rStickY;									//右スティックのY
	float m_lStickX;									//左スティックのX
	float m_lStickY;									//左スティックのY
	CVector3 m_cameraDirection;							//カメラの前方向
	bool m_drawflag = true;
	CVector3 m_RhandPos;
	CVector3 m_LhandPos;
	RigidBody* m_rigidBody;
	SPlayerStatus m_status;
	bool m_crouch = false;								//プレイヤーがしゃがんでいるか
	int m_shotCount = 0;
	static const int SHOTINTERVAL = 3;
	static const int SHOTSPEED = 2000;
	bool m_attackflag = false;
	int m_attackflagcount;
	bool m_killflag = false;
	int m_killflagcount;
	EnWeapon m_weapon = enWeapon_M4A1;
	M4A1 *m_m4a1;
	MP5  *m_mp5;
	Benelli_M4 *m_benelliM4;
	M110 *m_m110;

};
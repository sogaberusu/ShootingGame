#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"

class GameCamera;

class Player
{
public:
	Player();
	~Player();
	void Update(Camera& camera, int i);
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
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
		return m_handPos;
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
private:
	void InitAnimation();								//アニメーションの初期化
	void Move(Camera& camera, int i);					//移動処理
	void Turn(int i);									//回転処理
	enum EnAnimation {
		enAnimation_Idle,
		enAnimation_Walk_Forward,
		enAnimation_Walk_Back,
		enAnimation_Walk_Right,
		enAnimation_Walk_Left,
		enAnimation_Run,
		enAnimation_Jump_Start,
		enAnimation_Jump_Air,
		enAnimation_Jump_Land,
		enAnimation_Crouch_Idle,
		enAnimation_Crouch_Walk,
		enAnimation_Crouch_Reload,
		enAnimation_Crouch_Shoot,
		enAnimation_Reload,
		enAnimation_Shoot,
		enAnimation_Num
	};
	enum EnState {
		enState_Idle,
		enState_Walk_Forward,
		enState_Walk_Back,
		enState_Walk_Right,
		enState_Walk_Left,
		enState_Run,
		enState_Jump_Start,
		enState_Jump_Air,
		enState_Jump_Land,
		enState_Crouch_Idle,
		enState_Crouch_Walk,
		enState_Crouch_Reload,
		enState_Crouch_Shoot,
		enState_Reload,
		enState_Shoot,
		enState_Num
	};

	SkinModel m_model;									//スキンモデル。
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[enAnimation_Num];	//アニメーションクリップ。									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_scale = CVector3::One();					//拡大率。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	CVector3 m_forward;									//キャラクターの前方向
	CVector3 m_right;
	CharacterController m_charaCon;						//キャラクターコントローラー
	EnState m_state = enState_Idle;						//状態
	bool m_cameratype = EnCameraType::enType_TPS;		//カメラ
	float m_rStickX;									//右スティックのX
	float m_rStickY;									//右スティックのY
	float m_lStickX;									//左スティックのX
	float m_lStickY;									//左スティックのY
	CVector3 m_cameraDirection;							//カメラの前方向
	bool m_drawflag = true;
	CVector3 m_handPos;
};
#pragma once
#include "character/CharacterController.h"
#include "Stone.h"

class Goblin
{
public:
	Goblin();
	~Goblin();
	void Update();
	void Draw();
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
private:
	void InitAnimation();
	void Move();
	enum EnAnimation {
		enAnimation_Idle,
		enAnimation_walk,
		enAnimation_Jump
	};

	enum EnState {
		enState_Idle,
		enState_walk,
		enState_Jump,
		enState_Num
	};
	SkinModel m_model;									//スキンモデル
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[enState_Num];		//アニメーションクリップ。
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_scale = CVector3::One();					//拡大率。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	CharacterController m_charaCon;
	EnState m_state = enState_Idle;
	Stone m_stone;
};

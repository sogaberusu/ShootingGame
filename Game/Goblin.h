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
	SkinModel m_model;									//�X�L�����f��
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[enState_Num];		//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	CharacterController m_charaCon;
	EnState m_state = enState_Idle;
	Stone m_stone;
};

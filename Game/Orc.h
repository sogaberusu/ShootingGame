#pragma once
#include "character/CharacterController.h"

class Orc
{
public:
	Orc();
	~Orc();
	void Update();
	void Draw();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	void InitAnimation();
	void Move();
	enum EnAnimation {
		enAnimation_Idle,
		enAnimation_walk
	};

	enum EnState {
		enState_Idle,
		enState_walk,
		enState_Num
	};
	SkinModel m_model;									//�X�L�����f��
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[enState_Num];		//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	EnState m_state = enState_Idle;
};

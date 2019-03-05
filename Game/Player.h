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
	void InitAnimation();								//�A�j���[�V�����̏�����
	void Move(Camera& camera, int i);					//�ړ�����
	void Turn(int i);									//��]����
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
		enState_Reload,
		enState_Shoot,
		enState_Num
	};

	SkinModel m_model;									//�X�L�����f���B
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[enAnimation_Num];	//�A�j���[�V�����N���b�v�B									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	CVector3 m_forward;									//�L�����N�^�[�̑O����
	CVector3 m_right;
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	EnState m_state = enState_Idle;						//���
	bool m_cameratype = EnCameraType::enType_TPS;		//�J����
	float m_rStickX;									//�E�X�e�B�b�N��X
	float m_rStickY;									//�E�X�e�B�b�N��Y
	float m_lStickX;									//���X�e�B�b�N��X
	float m_lStickY;									//���X�e�B�b�N��Y
	CVector3 m_cameraDirection;							//�J�����̑O����
	bool m_drawflag = true;
};
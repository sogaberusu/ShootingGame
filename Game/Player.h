#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"
#include "Benelli_M4.h"
#include "M4A1.h"
#include "M110.h"
#include "SMAW.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class GameCamera;
struct SPlayerStatus
{
	int HitPoint = 100;				//�̗�
	int Kills = 0;					//�L����
	int Attack = 30;				//�U����
	int Ammo = 30;					//�c�e��
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
		return m_handPos;
	}
	SPlayerStatus GetStatus()
	{
		return m_status;
	}
	void SetHitPoint(int hp)
	{
		m_status.HitPoint = hp;
	}
	void SetKills(int kills)
	{
		m_status.Kills = kills;
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
	int GetAmmo()
	{
		return m_status.Ammo;
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
private:
	void InitAnimation();								//�A�j���[�V�����̏�����
	void Move(Camera& camera, int PlayerNumber);					//�ړ�����
	void Turn(int PlayerNumber);									//��]����
	enum EnAnimation {
		enAnimation_Idle,
		enAnimation_Walk_Forward,
		enAnimation_Walk_Back,
		enAnimation_Walk_Right,
		enAnimation_Walk_Left,
		enAnimation_Walk_Shoot,
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
		enAnimation_Num
	};
	enum EnState {
		enState_Idle,
		enState_Walk_Forward,
		enState_Walk_Back,
		enState_Walk_Right,
		enState_Walk_Left,
		enState_Walk_Shoot,
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
		enState_Num
	};

	SkinModel m_model;									//�X�L�����f���B
	SkinModel m_model_debag;							//�X�L�����f���B
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[enAnimation_Num];	//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	CVector3 m_forward;									//�L�����N�^�[�̑O����
	CVector3 m_right;									//�L�����N�^�[�̉E����
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	EnState m_state = enState_Idle;						//���
	bool m_cameratype = EnCameraType::enType_TPS;		//�J����
	float m_rStickX;									//�E�X�e�B�b�N��X
	float m_rStickY;									//�E�X�e�B�b�N��Y
	float m_lStickX;									//���X�e�B�b�N��X
	float m_lStickY;									//���X�e�B�b�N��Y
	CVector3 m_cameraDirection;							//�J�����̑O����
	bool m_drawflag = true;
	CVector3 m_handPos;
	RigidBody* m_rigidBody;
	M110 m_m110;
	SMAW m_smaw;
	Benelli_M4 m_benelli_m4;
	SPlayerStatus m_status;
	CSoundSource m_M4A1_Shot;				//SE�B
	bool m_crouch = false;					//�v���C���[�����Ⴊ��ł��邩
	int m_shotCount = 0;
	static const int SHOTINTERVAL = 3;
	static const int SHOTSPEED = 2000;
};
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
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class GameCamera;
struct SPlayerStatus
{
	int HitPoint = 100;				//�̗�
	int Kills = 0;					//�L����
	int HealTimer = 0;				//�����񕜂���܂ł̎���
	int Grenades = 2;				//�O���l�[�h�̏�����
	float CaptureTime = 0.0f;
};
class Player
{
public:
	
	Player(int playerNo);
	~Player();
	//�X�V
	void Update(Camera& camera, int PlayerNumber);
	//�`��
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	//�V���G�b�g�`��
	void SilhouetteDrwa(Camera& camera, int ViewportNumber, int PlayerNumber);
	//�v���C���[�̏�Ԃ�\��
	enum EnState {
		enState_Idle,				//�A�C�h��
		enState_Walk_Forward,		//�O����
		enState_Walk_Back,			//������
		enState_Walk_Right,			//�E����
		enState_Walk_Left,			//������
		enState_Walk_Shoot,			//��������
		enState_Walk_Reload,		//�����Ȃ��烊���[�h
		enState_Run,				//�_�b�V��
		enState_Jump_Start,			//�W�����v�Ԃ�
		enState_Jump_Air,			//�W�����v��
		enState_Jump_Land,			//���n
		enState_Crouch_Idle,		//���Ⴊ�݃A�C�h��
		enState_Crouch_Reload,		//���Ⴊ�݃����[�h
		enState_Crouch_Shoot,		//���Ⴊ�݌���
		enState_Crouch_Walk_Shoot,	//���Ⴊ�ݕ�������
		enState_Crouch_Walk_Forward,//���Ⴊ�ݑO����
		enState_Reload,				//�����[�h
		enState_Shoot,				//�e�۔���
		enState_Damage,				//�_���[�W�����炤
		enState_Death,				//���S
		enState_Grenade,			//�O���l�[�h�𓊂���
		enState_Num					//�v���C���[�̏�Ԑ�
	};
	enum EnPart
	{
		enPart_Head,				//���̍���
		enPart_Body,				//�̂̍���
		enPart_LeftLeg,				//�����̍���
		enPart_RightLeg,			//�E���̍���
		enPart_Num					//�v���C���[1�̂̍��̂̐�
	};
	//�v���C���[�̍��W��ݒ�
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	//�v���C���[�̉�]��ݒ�
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	//�v���C���[�̍��W��Ԃ�
	CVector3 GetPosition()
	{
		return m_position;
	}
	//�v���C���[�̈ړ����x��Ԃ�
	CVector3 GetMoveSpped()
	{
		return m_moveSpeed;
	}
	//�v���C���[�̑O������Ԃ�
	CVector3 GetForward()
	{
		return m_forward;
	}
	//�v���C���[�̉E������Ԃ�
	CVector3 GetRight()
	{
		return m_right;
	}
	//�E�X�e�B�b�N��x�̒l��Ԃ�
	float GetRStickX()
	{
		return m_rStickX;
	}
	//�E�X�e�B�b�N��y�̒l��Ԃ�
	float GetRStickY()
	{
		return m_rStickY;
	}
	//���X�e�B�b�N��x�̒l��Ԃ�
	float GetLStickX()
	{
		return m_lStickX;
	}
	//���X�e�B�b�N��y�̒l��Ԃ�
	float GetLStickY()
	{
		return m_lStickY;
	}
	//�v���C���[�̎�̍��W��Ԃ�
	CVector3 GetHandPos()
	{
		return m_rHandPos;
	}
	//�v���C���[�̃X�e�[�^�X��Ԃ�
	SPlayerStatus GetStatus()
	{
		return m_status;
	}
	//�v���C���[�̃q�b�g�|�C���g��ݒ肷��
	void SetHitPoint(int hp)
	{
		m_status.HitPoint = hp;
	}
	//�v���C���[�����񂾂炷�鏈��
	void SetDead()
	{
		m_state = enState_Death;
		m_deadflag = true;
		m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_Head].GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_Body].GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_LeftLeg].GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_RightLeg].GetBody()->setUserIndex(enCollisionAttr_Default);
	}
	//�v���C���[�̃L������ݒ肷��
	void SetKills(int kills)
	{
		m_status.Kills = kills;
	}
	//�v���C���[�������񕜂���܂ł̎��Ԃ�ݒ肷��
	void SetHealTimer(int timer)
	{
		m_status.HealTimer = timer;
	}
	//�J�����̕�����ݒ肷��
	void SetCameraDirection(CVector3 direction)
	{
		m_cameraDirection = direction;
	}
	//�v���C���[��`�悷�邩�̃t���O��false�ɂ���
	void DrawSetFalse()
	{
		m_drawflag = false;
	}
	//�v���C���[��`�悷�邩�̃t���O��true�ɂ���
	void DrawSetTrue()
	{
		m_drawflag = true;
	}
	//�v���C���[�̃X�e�[�^�X��Ԃ�
	EnState GetState()
	{
		return m_state;
	}
private:
	//�e�ۂ𔭎˂���
	void Shot(int PlayerNumber,Camera& camera);
public:
	enum EnCameraType {
		enType_TPS,					//TPS�J����
		enType_FPS					//FPS�J����
	};
	//���̃J�����̏�Ԃ�Ԃ�
	bool GetCameraType()
	{
		return m_cameratype;
	}
	//�J�����̏�Ԃ�ݒ肷��
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	//�X�L�����f����Ԃ�
	SkinModel GetSkinModel()
	{
		return m_model;
	}
	//�v���C���[�����Ⴊ��ł��邩��Ԃ�
	bool GetCrouch()
	{
		return m_crouch;
	}
	//������Ԃ�
	int GetRandom(int min, int max)
	{
		return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
	}
	//�v���C���[�̃L������Ԃ�
	int GetKills()
	{
		return m_status.Kills;
	}
	//�v���C���[��`�悷�邩�̃t���O��Ԃ�
	bool GetDrawFlag()
	{
		return m_drawflag;
	}
	//��]��Ԃ�
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	//�v���C���[�̃q�b�g�|�C���g��Ԃ�
	int GetHitPoint()
	{
		return m_status.HitPoint;
	}
	//�O���l�[�h����Ԃ�
	int GetGrenade()
	{
		return m_status.Grenades;
	}
	//�U���������������Ƀq�b�g�}�[�J�[��\������t���O��true�ɂ���
	void SetAttackTrue()
	{
		m_attackflag = true;
	}
	//�U���������������Ƀq�b�g�}�[�J�[��\������t���O��false�ɂ���
	void SetAttackFalse()
	{
		m_attackflag = false;
	}
	//�q�b�g�}�[�J�[��\�����鎞�Ԃ�ݒ肷��
	void SetAttackCount(int time)
	{
		m_attackflagcount = time;
	}
	//�q�b�g�}�[�J�[��\������t���O��Ԃ�
	bool GetAttackFlag()
	{
		return m_attackflag;
	}
	//�L���}�[�J�[��\������t���O��true�ɂ���
	void SetKillTrue()
	{
		m_killflag = true;
	}
	//�L���}�[�J�[��\������t���O��false�ɂ���
	void SetKillFalse()
	{
		m_killflag = false;
	}
	//�L���}�[�J�[��\�����鎞�Ԃ�ݒ肷��
	void SetKillCount(int time)
	{
		m_killflagcount = time;
	}
	//�L���}�[�J�[��\�����鎞�Ԃ�ݒ肷��
	bool GetKillFlag()
	{
		return m_killflag;
	}
	//�������Ă���e��Ԃ�
	EnWeapon GetWeapon()
	{
		return m_weapon;
	}
	//��������e��ݒ肷��
	void SetWeapon(EnWeapon weapon)
	{
		m_weapon = weapon;
	}
	//�e�̃C���X�^���X��ݒ肷��
	void SetWeaponInstance(M4A1 *m4a1,MP5 *mp5,Benelli_M4 *benelliM4,M110 *m110)
	{
		m_m4a1 = m4a1;
		m_mp5  = mp5;
		m_benelliM4 = benelliM4;
		m_m110 = m110;
	}
	//�v���C���[�����������Ă��邩�̃t���O��Ԃ�
	bool GetIsFlag()
	{
		return m_isflag;
	}
	//�v���C���[�����������Ă��邩�ǂ����̃t���O��ݒ肷��
	void SetIsFlag(bool flag)
	{
		m_isflag = flag;
	}
	//�����m�ۂ��Ă��鎞�Ԃ�Ԃ�
	float GetCaptureTime()
	{
		return m_status.CaptureTime;
	}
	//�L�����N�^�[�R���g���[���[��Ԃ�
	CharacterController GetCharaCon()
	{
		return m_charaCon;
	}
	//�v���C���[���|���ꂽ���ǂ����̃t���O��Ԃ�
	bool GetDeadFlag()
	{
		return m_deadflag;
	}
	//�v���C���[�������m�ۂ��Ă��鎞�Ԃ�ݒ肷��
	void SetCaptureTime(float time)
	{
		m_status.CaptureTime = time;
	}
	void CreateHeadCollider(int playerNo);				//�w�b�h�V���b�g�p�̓����蔻����쐬����
	void CreateBodyCollider(int playerNo);				//�̂̓����蔻����쐬����
	void CreateLeftLegCollider(int playerNo);			//�����̓����蔻����쐬����
	void CreateRightLegCollider(int playerNo);			//�E���̓����蔻����쐬����
private:
	void InitAnimation();								//�A�j���[�V�����̏�����
	void Move(Camera& camera, int PlayerNumber);		//�ړ�����
	void Turn(int PlayerNumber);						//��]����
	//�v���C���[�̃A�j���[�V����
	enum EnAnimation {
		enAnimation_Idle,								//�A�C�h��
		enAnimation_Walk_Forward,						//�O����
		enAnimation_Walk_Back,							//������
		enAnimation_Walk_Right,							//�E����
		enAnimation_Walk_Left,							//������
		enAnimation_Walk_Shoot,							//�����Ȃ���e������
		enAnimation_Walk_Reload,						//�����Ȃ��烊���[�h
		enAnimation_Run,								//����
		enAnimation_Jump_Start,							//�W�����v�J�n
		enAnimation_Jump_Air,							//������
		enAnimation_Jump_Land,							//���n
		enAnimation_Crouch_Idle,						//���Ⴊ�݃A�C�h��
		enAnimation_Crouch_Reload,						//���Ⴊ�݃����[�h
		enAnimation_Crouch_Shoot,						//���Ⴊ�݌���
		enAnimation_Crouch_Walk_Shoot,					//���Ⴊ�ݕ�������
		enAnimation_Crouch_Walk_Forward,				//���Ⴊ�ݑO����
		enAnimation_Reload,								//�����[�h
		enAnimation_Shoot,								//�e������
		enAnimation_Damage,								//�_���[�W�����炤
		enAnimation_Death,								//�|���
		enAnimation_Grenade,							//�O���l�[�h�𓊂���
		enAnimation_Num									//�A�j���[�V������
	};
	
	SkinModel m_model;									//�X�L�����f���B
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
	bool m_drawflag = true;								//fps���_�̎��Ɏ����̃��f����\�����Ȃ����߂Ɏg��
	CVector3 m_rHandPos;								//���f���̉E��̍��W
	CVector3 m_lHandPos;								//���f���̍���̍��W
	RigidBody m_rigidBody[enPart_Num];					//����
	SPlayerStatus m_status;								//�v���C���[�̃X�e�C�^�X
	bool m_crouch = false;								//�v���C���[�����Ⴊ��ł��邩
	bool m_attackflag = false;							//�U���������������ɔ����}�[�J�[���o�����߂̃t���O
	int m_attackflagcount;								//�����}�[�J�[��\�����鎞��
	bool m_killflag = false;							//�G��|�����Ƃ��ɐԂ��}�[�J�[���o�����߂̃t���O
	int m_killflagcount;								//�Ԃ��}�[�J�[��\�����鎞��
	EnWeapon m_weapon = enWeapon_M4A1;                  //�������Ă��镐�������
	M4A1 *m_m4a1;										//����@�A�T���g���C�t��
	MP5  *m_mp5;										//����@�T�u�}�V���K��
	Benelli_M4 *m_benelliM4;							//����@�V���b�g�K��
	M110 *m_m110;										//����@�X�i�C�p�[
	bool m_isflag = false;								//�v���C���[�������m�ۂ��Ă���ƃV���G�b�g�`�悷��t���O						
	bool m_deadflag = false;							//�v���C���[���|���ꂽ�Ƃ���true�ɂȂ�t���O
	CapsuleCollider m_headCollider;						//�w�b�h�V���b�g�p�̃J�v�Z���R���C�_�[
	CapsuleCollider	m_bodyCollider;						//���̗p�̃J�v�Z���R���C�_�[
	CapsuleCollider	m_leftlegCollider;					//�����p�̃J�v�Z���R���C�_�[
	CapsuleCollider	m_rightlegCollider;					//�E���p�̃J�v�Z���R���C�_�[
};
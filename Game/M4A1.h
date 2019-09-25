#pragma once
#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Player;

class M4A1
{
	struct SGunStatus
	{
	int Ammo = 30;									//�c�e��
	int Attack = 30;								//�U����
	static constexpr float SHOTINTERVAL = 0.4f;		//�A�ˑ��x ���l������������Ƒ����Ȃ�
	
	};
public:
	M4A1();
	~M4A1();
	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update();
	
	void Draw(Camera& camera,int ViewportNumber, int PlayerNumber);
	void Shot(CVector3 target, int PlayerNumber);
	void SetInstance(Player *player)
	{
		m_player = player;
	}
	int GetAmmo()
	{
		return m_gunStatus.Ammo;
	}
	void SetAmmo(int ammo)
	{
		m_gunStatus.Ammo = ammo;
	}
	void SetShootIntervalNow(float interval)
	{
		m_shootIntervalNow = interval;
	}
private:
	SkinModel m_model;									//���f��
	Player *m_player;									//�v���C���[�̃C���X�^���X
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CSoundSource m_gunshot;								//SE
	SGunStatus m_gunStatus;								//�e�̃X�e�C�^�X
	float m_shootIntervalNow = 0.0f;					//�e�𔭎˂���^�C�~���O
};


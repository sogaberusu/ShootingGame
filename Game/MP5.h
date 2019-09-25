#pragma once
#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Player;

class MP5
{
	struct SGunStatus
{
	int Ammo = 30;										//�c�e��
	int Attack = 20;									//�U����
	static constexpr float SHOTINTERVAL = 0.2f;			//�A�ˑ��x ���l������������Ƒ����Ȃ�
};
public:
	MP5();
	~MP5();
	//�X�V
	void Update();
	//�`��
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	//�e�𔭎�
	void Shot(CVector3 target, int PlayerNumber);
	//���˂���^�C�~���O
	void SetInstance(Player *player)
	{
		m_player = player;
	}
	//�c�e����Ԃ�
	int GetAmmo()
	{
		return m_gunStatus.Ammo;
	}
	//�c�e����ݒ肷��
	void SetAmmo(int ammo)
	{
		m_gunStatus.Ammo = ammo;
	}
	//�e�𔭎˂���^�C�~���O��ݒ�
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
	SGunStatus m_gunStatus;								//�e�̏��
	float m_shootIntervalNow = 0.0f;					//�e�����^�C�~���O
};


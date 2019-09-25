#pragma once
#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Player;

class Benelli_M4
{
	struct SGunStatus
	{
		int Ammo = 7;									//�c�e��
		int Attack = 10;								//�U����
		static constexpr float SHOTINTERVAL = 1.0f;		//�A�ˑ��x ���l������������Ƒ����Ȃ�
		static const int SCATTER = 10;					//�����ɔ��˂���e�̐�
		int BulletLife = 10;							//�e��������܂ł̎���

	};
public:
	Benelli_M4();
	~Benelli_M4();
	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update();
	//�`��
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	//�e�̔���
	void Shot(CVector3 target, int PlayerNumber);
	//�v���C���[�̃C���X�^���X�����炤
	void SetInstance(Player *player)
	{
		m_player = player;
	}
	//�c�e�������炤
	int GetAmmo()
	{

		return m_gunStatus.Ammo;
	}
	//�����[�h�ł���
	void SetAmmo(int ammo)
	{
		m_gunStatus.Ammo = ammo;
	}
	//�e�����^�C�~���O
	void SetShootIntervalNow(float interval)
	{
		m_shootIntervalNow = interval;
	}
	//�V���b�g�K���̒e���΂炯������̂Ɏg��
	float GetRandom()
	{
		while (true)
		{
			auto temp = (float)rand() / ((float)RAND_MAX *10.0f) - 0.05f;
			//�����Ȓl��Ԃ��Ȃ��悤�ɂ���
			if (temp > 0.01f || temp < -0.01f) {
				return temp;
				break;
			}
		}
	}
private:
	SkinModel m_model;									//���f��
	Player *m_player;									//�v���C���[�̃C���X�^���X
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CSoundSource m_gunshot;								//SE
	SGunStatus m_gunStatus;                             //�e�̃X�e�[�^�X
	float m_shootIntervalNow = 0.0f;                    //�e������
};
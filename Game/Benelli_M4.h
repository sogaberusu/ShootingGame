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
		static const int SCATTER = 15;					//�����ɔ��˂���e�̐�
		int BulletLife = 10;							//�e��������܂ł̎���

	};
public:
	Benelli_M4();
	~Benelli_M4();
	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="ViewportNumber"></param>
	/// <param name="PlayerNumber"></param>
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
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
	SGunStatus GetGunStatus()
	{
		return m_gunStatus;
	}
	void SetShootIntervalNow(float interval)
	{
		m_shootIntervalNow = interval;
	}
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
	SGunStatus m_gunStatus;
	float m_shootIntervalNow = 0.0f;
};
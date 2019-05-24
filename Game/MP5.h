#pragma once
#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Player;

class MP5
{
	struct SGunStatus
{
	int Ammo = 30;										//残弾数
	int Attack = 20;									//攻撃力
	static constexpr float SHOTINTERVAL = 0.2f;			//連射速度 数値を小さくすると早くなる
};
public:
	MP5();
	~MP5();
	void Update();
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
private:
	SkinModel m_model;
	Player *m_player;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CSoundSource m_gunshot;								//SE
	SGunStatus m_gunStatus;
	float m_shootIntervalNow = 0.0f;
};


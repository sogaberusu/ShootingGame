#pragma once
#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Player;

class M4A1
{
	struct SGunStatus
	{
	int Ammo = 30;									//残弾数
	int Attack = 30;								//攻撃力
	static constexpr float SHOTINTERVAL = 0.3f;		//連射速度 数値を小さくすると早くなる
	
	};
public:
	M4A1();
	~M4A1();
	/// <summary>
	/// アップデート
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
private:
	SkinModel m_model;									//モデル
	Player *m_player;									//プレイヤーのインスタンス
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CSoundSource m_gunshot;								//SE
	SGunStatus m_gunStatus;
	float m_shootIntervalNow = 0.0f;
};


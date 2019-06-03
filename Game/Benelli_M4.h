#pragma once
#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Player;

class Benelli_M4
{
	struct SGunStatus
	{
		int Ammo = 7;									//残弾数
		int Attack = 10;								//攻撃力
		static constexpr float SHOTINTERVAL = 1.0f;		//連射速度 数値を小さくすると早くなる
		static const int SCATTER = 15;					//同時に発射する弾の数
		int BulletLife = 10;							//弾が消えるまでの時間

	};
public:
	Benelli_M4();
	~Benelli_M4();
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
	float GetRandom()
	{
		while (true)
		{
			auto temp = (float)rand() / ((float)RAND_MAX *10.0f) - 0.05f;
			//小さな値を返さないようにする
			if (temp > 0.01f || temp < -0.01f) {
				return temp;
				break;
			}
		}
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
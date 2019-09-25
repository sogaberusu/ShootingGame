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
	//更新
	void Update();
	//描画
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	//弾を発射
	void Shot(CVector3 target, int PlayerNumber);
	//発射するタイミング
	void SetInstance(Player *player)
	{
		m_player = player;
	}
	//残弾数を返す
	int GetAmmo()
	{
		return m_gunStatus.Ammo;
	}
	//残弾数を設定する
	void SetAmmo(int ammo)
	{
		m_gunStatus.Ammo = ammo;
	}
	//弾を発射するタイミングを設定
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
	SGunStatus m_gunStatus;								//銃の状態
	float m_shootIntervalNow = 0.0f;					//弾を撃つタイミング
};


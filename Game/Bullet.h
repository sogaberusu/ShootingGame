#pragma once
#include "BulletManager.h"
#include "BulletController.h"
class Bullet
{
public:
	Bullet();
	Bullet(CVector3 pos,int tag,int attack);
	~Bullet();
	void Update();
	void Draw(Camera& camera);
	//弾に座標を設定する
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
	}
	//弾の座標を返す
	CVector3 GetPosition()
	{
		return m_pos;
	}
	//弾の速度を返す
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	//弾の速度を設定する
	void SetMoveSpeed(CVector3 speed)
	{
		m_moveSpeed = speed;
	}
	//弾が消えているか消えていないかを返す
	bool IsDead()
	{
		return m_isDead;
	}
	//弾を消す
	void SetBulletDead()
	{
		m_isDead = true;
	}
	//弾が自然消滅するまでの時間を設定する
	void SetLife(int life)
	{
		m_life = life;
	}
private:
	SkinModel m_model;							//モデル。
	CVector3 m_pos = CVector3::Zero();			//座標。
	CVector3 m_moveSpeed = CVector3::Zero();	//移動速度。
	int m_attack;								//攻撃力
	int m_life = INT_MAX;						//弾の消滅までの時間
	bool m_isDead = false;                      //弾を消すフラグ
	BulletController m_bulletController;        //弾の当たり判定をとる
};

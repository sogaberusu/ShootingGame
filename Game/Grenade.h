#pragma once
#include "GrenadeController.h"
#include "physics/CollisionAttr.h"

class Grenade
{
public:
	Grenade(CVector3 pos, int PlayerNumber, CVector3 target);
	~Grenade();
	/// <summary>
	/// アップデート
	/// </summary>
	void Update(int PlayerNumber);
	void Draw(Camera& camera);
	bool IsDead()
	{
		return m_isDead;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SpriteDrawFlag(bool draw)
	{
		m_spriteDrawflag = draw;
	}
	bool GetSpriteDrawFlag()
	{
		return m_spriteDrawflag;
	}
	int GetThrowPlayer()
	{
		return m_throwplayer;
	}
private:
	GrenadeController m_grenadeController;				//グレネードコントローラー
	SkinModel m_model;									//モデル
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_target = CVector3::Zero();
	int m_life = 100;									//爆発までの時間		
	bool m_isDead = false;								//爆発しているか
	bool m_spriteDrawflag = false;
	int m_throwplayer;										//誰が投げたのか記録しておく
};
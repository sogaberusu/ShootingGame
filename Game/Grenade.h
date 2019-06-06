#pragma once
class Grenade
{
public:
	Grenade(CVector3 pos,CVector3 forward);
	~Grenade();
	/// <summary>
	/// アップデート
	/// </summary>
	void Update();
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
private:
	SkinModel m_model;									//モデル
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_forward = CVector3::Zero();
	int m_life = 100;									//爆発までの時間		
	bool m_isDead = false;								//爆発しているか
	bool m_spriteDrawflag = false;
};


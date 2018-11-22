#pragma once
class Stone
{
public:
	Stone();
	~Stone();
	void Update();
	void Draw(Camera& camera);
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
	}
	CVector3 GetPosition()
	{
		return m_pos;
	}
	void SetMoveSpeed(CVector3 speed)
	{
		m_moveSpeed += speed;
	}
	bool IsDead()
	{
		return m_isDead;
	}
	void SetStoneDead() 
	{
		m_isDead = true;
	}
private:
	SkinModel m_model;							//モデル。
	CVector3 m_pos = CVector3::Zero();			//座標。
	CVector3 m_moveSpeed = CVector3::Zero();	//移動速度。
	bool m_isDead = false;
};

#pragma once
#include "BulletManager.h"
#include "BulletController.h"
class Bullet
{
public:
	Bullet();
	Bullet(CVector3 pos,int tag);
	~Bullet();
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
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetMoveSpeed(CVector3 speed)
	{
		m_moveSpeed += speed;
	}
	bool IsDead()
	{
		return m_isDead;
	}
	void SetBulletDead()
	{
		m_isDead = true;
	}
private:
	SkinModel m_model;							//���f���B
	CVector3 m_pos = CVector3::Zero();			//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();	//�ړ����x�B
	bool m_isDead = false;
	BulletController m_bulletController;
};

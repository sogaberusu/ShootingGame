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
		m_moveSpeed = speed;
	}
	bool IsDead()
	{
		return m_isDead;
	}
	void SetBulletDead()
	{
		m_isDead = true;
	}
	void SetLife(int life)
	{
		m_life = life;
	}
private:
	SkinModel m_model;							//���f���B
	CVector3 m_pos = CVector3::Zero();			//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();	//�ړ����x�B
	int m_attack;								//�U����
	int m_life = INT_MAX;						//�e�̏��ł܂ł̎���
	bool m_isDead = false;
	BulletController m_bulletController;
};

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
	//�e�ɍ��W��ݒ肷��
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
	}
	//�e�̍��W��Ԃ�
	CVector3 GetPosition()
	{
		return m_pos;
	}
	//�e�̑��x��Ԃ�
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	//�e�̑��x��ݒ肷��
	void SetMoveSpeed(CVector3 speed)
	{
		m_moveSpeed = speed;
	}
	//�e�������Ă��邩�����Ă��Ȃ�����Ԃ�
	bool IsDead()
	{
		return m_isDead;
	}
	//�e������
	void SetBulletDead()
	{
		m_isDead = true;
	}
	//�e�����R���ł���܂ł̎��Ԃ�ݒ肷��
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
	bool m_isDead = false;                      //�e�������t���O
	BulletController m_bulletController;        //�e�̓����蔻����Ƃ�
};

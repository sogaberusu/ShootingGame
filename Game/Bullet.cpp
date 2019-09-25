#include "stdafx.h"
#include "Bullet.h"
#include "Game.h"


Bullet::Bullet()
{
}

Bullet::Bullet(CVector3 pos,int tag,int attack)
{
	m_model.Init(L"Assets/modelData/Bullet.cmo");

	m_bulletController.Init(2.5f,1.0f, pos, tag);
	//�e�ɍU���͂�ݒ�
	m_attack = attack;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_pos = m_bulletController.Execute(1.0f / 60.0f, m_moveSpeed,m_attack);
	
	m_isDead = m_bulletController.GetIsDead();
	//�e���͈͊O�ɏo���������
	if (m_pos.x > 2000 || m_pos.x < -2000 ||
		m_pos.y > 500 || m_pos.y < -500 ||
		m_pos.z > 2000 || m_pos.z < -2000)
	{
		m_isDead = true;
	}
	//�V���b�g�K���̎��ɒe�����R���ł�����̂Ɏg��
	m_life--;
	if (m_life <= 0)
	{
		m_isDead = true;
	}
	//�X�V
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	
}
void Bullet::Draw(Camera& camera)
{
	//�`��
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), enNormalDraw);
}
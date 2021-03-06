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
	//弾に攻撃力を設定
	m_attack = attack;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_pos = m_bulletController.Execute(1.0f / 60.0f, m_moveSpeed,m_attack);
	
	m_isDead = m_bulletController.GetIsDead();
	//弾が範囲外に出たら消える
	if (m_pos.x > 2000 || m_pos.x < -2000 ||
		m_pos.y > 500 || m_pos.y < -500 ||
		m_pos.z > 2000 || m_pos.z < -2000)
	{
		m_isDead = true;
	}
	//ショットガンの時に弾を自然消滅させるのに使う
	m_life--;
	if (m_life <= 0)
	{
		m_isDead = true;
	}
	//更新
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	
}
void Bullet::Draw(Camera& camera)
{
	//描画
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), enNormalDraw);
}
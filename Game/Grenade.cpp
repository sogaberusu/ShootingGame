#include "stdafx.h"
#include "Grenade.h"
#include "Game.h"

Grenade::Grenade(CVector3 pos, int PlayerNumber, CVector3 target)
{
	m_model.Init(L"Assets/modelData/Grenade.cmo");
	m_position = pos;
	m_target = target * 2000;
	m_grenadeController.Init(10.0f, 5.0f, m_position,m_target);
	m_grenadeController.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Player1_Bullet + PlayerNumber);
	m_throwplayer = PlayerNumber;
}


Grenade::~Grenade()
{
}

void Grenade::Update(int PlayerNumber)
{
	

	if (m_position.y > 10.0f)
	{
		m_position = m_grenadeController.Execute(1.0f / 60.0f);
	}
	m_life--;
	if (m_life <= 0)
	{
		g_game->GetExplosionEffect(PlayerNumber).Play(m_position, CQuaternion::Identity(), CVector3::One());
		m_isDead = true;
	}
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Grenade::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), 0);
}
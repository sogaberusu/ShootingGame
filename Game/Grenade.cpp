#include "stdafx.h"
#include "Grenade.h"


Grenade::Grenade(CVector3 pos,CVector3 forward)
{
	m_model.Init(L"Assets/modelData/Grenade.cmo");

	m_position = pos;

	m_forward = forward;
}


Grenade::~Grenade()
{
}

void Grenade::Update()
{
	/*m_position += m_forward * 20.0f;
	m_position.y -= 200.0f;*/
	m_life--;
	if (m_life <= 0)
	{
		m_isDead = true;
	}
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Grenade::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), 0);
}
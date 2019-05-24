#include "stdafx.h"
#include "WeaponManager.h"
#include"Player.h"

WeaponManager::WeaponManager()
{
}
WeaponManager::~WeaponManager()
{
}

void WeaponManager::Update()
{
	m_position = m_player->GetHandPos();

	m_rotation = m_player->GetRotation();



	m_m4a1.Update(m_position,m_rotation);

	//m_mp5.Update(position);
}

void WeaponManager::Draw(Camera& camera, int ViewportNumber, int PlayerNumber)
{
	m_m4a1.Draw(camera, ViewportNumber, PlayerNumber);
}
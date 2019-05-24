#pragma once
#include "Benelli_M4.h"
#include "M4A1.h"
#include "M110.h"
#include "SMAW.h"
#include "MP5.h"
class Player;
class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();
	void Update();
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	void SetInstance(Player *player)
	{
		m_player = player;
	}
private:
	Player * m_player;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	M4A1 m_m4a1;
	MP5  m_mp5;
};


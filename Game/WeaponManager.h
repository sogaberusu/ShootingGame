#pragma once
#include "Benelli_M4.h"
#include "M4A1.h"
#include "M110.h"
#include "SMAW.h"
class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();
private:
	M110 m_m110;
	SMAW m_smaw;
	Benelli_M4 m_benelli_m4;
};


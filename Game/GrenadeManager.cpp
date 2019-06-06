#include "stdafx.h"
#include "GrenadeManager.h"
#include "Grenade.h"


GrenadeManager::GrenadeManager()
{
	//‰Šú‰»
	for (int i = 0; i < 4; i++)
	{
		m_player[i] = nullptr;
	}
}


GrenadeManager::~GrenadeManager()
{
	//‰ğ•ú
	for (int i = 0; i < 4; i++)
	{
		for (auto& Grenade : m_grenade[i]) {
			delete Grenade;
		}
	}
}

Grenade*GrenadeManager::NewGrenade(CVector3 pos, int PlayerNumber,CVector3 forward)
{
	Grenade* newGrenade = new Grenade(pos, forward);
	m_grenade[PlayerNumber].push_back(newGrenade);
	return newGrenade;
}

void GrenadeManager::Update()
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Grenade : m_grenade[i]) {
			Grenade->Update();
		}

		auto it = m_grenade[i].begin();
		while (it != m_grenade[i].end()) {
			if ((*it)->IsDead() == true) {
				delete *it;
				it = m_grenade[i].erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void GrenadeManager::Draw(Camera& camera)
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Grenade : m_grenade[i]) {
			Grenade->Draw(camera);
		}
	}
}
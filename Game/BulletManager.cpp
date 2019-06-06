#include "stdafx.h"
#include "BulletManager.h"
#include "Physics/CollisionAttr.h"
#include "Bullet.h"



BulletManager::BulletManager()
{
	//‰Šú‰»
	for (int i = 0; i < 4; i++)
	{
		m_player[i] = nullptr;
	}
}


BulletManager::~BulletManager()
{
	//‰ğ•ú
	for (int i = 0; i < 4; i++)
	{
		for (auto& Bullet : m_bullet[i]) {
			delete Bullet;
		}
	}
}

Bullet* BulletManager::NewBullet(CVector3 pos,int PlayerNumber,int Attack)
{
	Bullet* newBullet = new Bullet(pos, PlayerNumber,Attack);
	m_bullet[PlayerNumber].push_back(newBullet);
	return newBullet;
}

void BulletManager::Update()
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Bullet : m_bullet[i]) {
			Bullet->Update();
		}

		auto it = m_bullet[i].begin();
		while (it != m_bullet[i].end()) {
			if ((*it)->IsDead() == true) {
				delete *it;
				it = m_bullet[i].erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void BulletManager::Draw(Camera& camera)
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Bullet : m_bullet[i]) {
			Bullet->Draw(camera);
		}
	}
}
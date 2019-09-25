#include "stdafx.h"
#include "BulletManager.h"
#include "Physics/CollisionAttr.h"
#include "Bullet.h"
#include "Game.h"


BulletManager::BulletManager()
{
	//èâä˙âª
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		m_player[PlayerNo] = nullptr;
	}
}


BulletManager::~BulletManager()
{
	//âï˙
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		for (auto& Bullet : m_bullet[PlayerNo]) {
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
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		for (auto& Bullet : m_bullet[PlayerNo]) {
			Bullet->Update();
		}

		auto it = m_bullet[PlayerNo].begin();
		while (it != m_bullet[PlayerNo].end()) {
			if ((*it)->IsDead() == true) {
				delete *it;
				it = m_bullet[PlayerNo].erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void BulletManager::Draw(Camera& camera)
{
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		for (auto& Bullet : m_bullet[PlayerNo]) {
			Bullet->Draw(camera);
		}
	}
}
#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
#include "Player.h"

class Bullet;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	Bullet* NewBullet(CVector3 pos,int PlayerNumber, int Attack);
	void Update();
	void Draw(Camera& camera);
	void SetInstance(Player *player, int PlayerNumber)
	{
		m_player[PlayerNumber] = player;
	}
	Player* GetPlayer(int PlayerNumber)
	{
		return m_player[PlayerNumber];
	}
private:
	std::vector<Bullet*> m_bullet[4];					//�e�ۂ̉ϒ��z��B
	Player *m_player[4];								//�v���C���[�̃C���X�^���X
};


#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
#include "Player.h"
#include "Game.h"
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
	std::vector<Bullet*> m_bullet[PLAYERS];					//弾丸の可変長配列。
	Player *m_player[PLAYERS];								//プレイヤーのインスタンス
};


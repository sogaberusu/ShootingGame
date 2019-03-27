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
	Bullet* NewBullet(int PlayerNumber);
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
	///*!
	//	* @brief	初期化。
	//	*@param[in]	radius		カプセルコライダーの半径。
	//	*@param[in]	height		カプセルコライダーの高さ。
	//	*@param[in]	position	初期位置。
	//	*/
	//void Init(float radius, float height, const CVector3& position);
	///*!
	//	* @brief	実行。
	//	*@param[in]	deltaTime		経過時間。単位は秒。
	//	*@param[in, out]	moveSpeed		移動速度。内部で重力加速が計算され、その結果がmoveSpeedに反映されます。
	//	*@return 移動後のキャラクターの座標。
	//	*/
	//const CVector3& Execute(float deltaTime, CVector3& moveSpeed,Bullet& bullet);
	///*!
	//* @brief	剛体を物理エンジンから削除。。
	//*/
	//void RemoveRigidBoby();
private:
	//CVector3 			m_position = CVector3::Zero();	//座標
	//CapsuleCollider		m_collider;						//コライダー。
	//float				m_radius = 0.0f;				//コライダーの半径
	//float				m_height = 0.0f;				//コライダーの高さ
	//RigidBody			m_rigidBody;					//剛体。
	std::vector<Bullet*> m_bullet[4];					//弾丸の可変長配列。
	Player *m_player[4];								//プレイヤーのインスタンス
};


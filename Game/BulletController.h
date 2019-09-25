#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"

class Bullet;

class BulletController
{
public:
	BulletController();
	~BulletController()
	{
		RemoveRigidBoby();
	}
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="radius">
	/// カプセルコライダーの半径。 
	/// </param>
	/// <param name="height">
	/// カプセルコライダーの高さ。	
	/// </param>
	/// <param name="position">
	/// 初期位置。	
	/// </param>
	/// <param name="tag">
	/// コライダーの属性	
	/// </param>
	void Init(float radius, float height, const CVector3& position,int tag);
	/// <summary>
	///実行。
	/// </summary>
	/// <param name="deltaTime">
	/// 経過時間。単位は秒。
	/// </param>
	/// <param name="moveSpeed">
	/// 移動速度。内部で重力加速が計算され、その結果がmoveSpeedに反映されます。
	/// </param>
	/// <param name="attack">
	/// 攻撃力
	/// </param>
	/// <returns>
	/// 移動後のキャラクターの座標。
	/// </returns>
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed, int attack);
	/*!
	* @brief	剛体を物理エンジンから削除。。
	*/
	void RemoveRigidBoby();
	//弾が消えているかを返す
	bool GetIsDead()
	{
		return m_isDead;
	}
private:
	CVector3 			m_position = CVector3::Zero();	//座標
	CapsuleCollider		m_collider;						//コライダー。
	float				m_radius = 0.0f;				//コライダーの半径
	float				m_height = 0.0f;				//コライダーの高さ
	RigidBody			m_rigidBody;					//剛体。
	bool m_isDead = false;								//弾を消すかのフラグtrueで消える
};
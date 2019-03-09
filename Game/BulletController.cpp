#include "stdafx.h"
#include "BulletController.h"
#include "Physics/CollisionAttr.h"
#include "Bullet.h"


BulletController::BulletController()
{
}

namespace {
	//衝突したときに呼ばれる関数オブジェクト(壁用)
	struct SweepResultWall1 : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;						//衝突フラグ。
		btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を除外するためのメンバ。
												//衝突したときに呼ばれるコールバック関数。
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me ||
				convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Bullet
				) {
				//自分に衝突した。or 地面に衝突した。
			
				return 0.0f;
			}
			isHit = true;
			return 0.0f;
		}
	};
}
void BulletController::Init(float radius, float height, const CVector3& position)
{
	m_position = position;
	//コリジョン作成。
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);
	//剛体を初期化。
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Bullet);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	//m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_User);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);
}

const CVector3& BulletController::Execute(float deltaTime, CVector3& moveSpeed)
{
	//次の移動先となる座標を計算する。
	CVector3 nextPosition = m_position;
	//速度からこのフレームでの移動量を求める。オイラー積分。
	CVector3 addPos = moveSpeed;
	addPos *= deltaTime;
	nextPosition += addPos;

	CVector3 originalXZDir = addPos;
	originalXZDir.y = 0.0f;
	originalXZDir.Normalize();
	//XZ平面での衝突検出と衝突解決を行う。
	{
		//現在の座標から次の移動先へ向かうベクトルを求める。
		CVector3 addPos;
		addPos.Subtract(nextPosition, m_position);
		CVector3 addPosXZ = addPos;
		addPosXZ.y = 0.0f;
		//カプセルコライダーの中心座標 + 高さ*0.1の座標をposTmpに求める。
		CVector3 posTmp = m_position;
		posTmp.y += m_height * 0.5f + m_radius + m_height * 0.1f;
		//レイを作成。
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//始点はカプセルコライダーの中心座標 + 0.2の座標をposTmpに求める。
		start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
		//終点は次の移動先。XZ平面での衝突を調べるので、yはposTmp.yを設定する。
		end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

		SweepResultWall1 callback;
		callback.me = m_rigidBody.GetBody();
		//衝突検出。
		g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

		if (callback.isHit) {
			//当たった。
			//壁。
			m_isDead = true;
			return m_position;
		}
	}
	//XZの移動は確定。
	m_position.x = nextPosition.x;
	m_position.z = nextPosition.z;

	//移動確定。
	m_position = nextPosition;
	btRigidBody* btBody = m_rigidBody.GetBody();
	//剛体を動かす。
	btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	//@todo 未対応。 trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	return m_position;
}

/*!
* @brief	死亡したことを通知。
*/
void BulletController::RemoveRigidBoby()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
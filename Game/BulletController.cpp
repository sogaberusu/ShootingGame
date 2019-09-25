#include "stdafx.h"
#include "BulletController.h"
#include "Physics/CollisionAttr.h"
#include "Bullet.h"
#include "Game.h"
#include "HUD.h"


BulletController::BulletController()
{
}

namespace {
	//衝突したときに呼ばれる関数オブジェクト
	struct SweepResultWall1 : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;						//衝突フラグ。
		btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を除外するためのメンバ。
												//衝突したときに呼ばれるコールバック関数。
		int attack;								//攻撃力
		float headPower = 2.0f;					//頭に当たった時の倍率
		float bodyPower = 1.0f;					//体に当たった時の倍率
		float legPower = 0.7f;					//足に当たった時の倍率
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			int bulletTag = me->getUserIndex();
			bool isHitPlayer = false;
			//プレイヤーと弾丸の当たり判定
			//自分自身の弾丸に当たらないようにタグで判定する
			//プレイヤー1の頭に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_Head &&
				bulletTag != enCollisionAttr_Player1_Bullet && 
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo,attackPlayerNo,attack, headPower);
			}
			//プレイヤー2の頭に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_Head &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, headPower);
			}
			//プレイヤー3の頭に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_Head &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, headPower);
			}
			//プレイヤー4の頭に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_Head &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, headPower);
			}
			//プレイヤー1の胴体に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_Body &&
				bulletTag != enCollisionAttr_Player1_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//プレイヤー2の胴体に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_Body &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//プレイヤー3の胴体に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_Body &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//プレイヤー4の胴体に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_Body &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//プレイヤー1の左足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_LeftLeg &&
				bulletTag != enCollisionAttr_Player1_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー2の左足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_LeftLeg &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー3の左足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_LeftLeg &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー4の左足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_LeftLeg &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー1の右足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_RightLeg &&
				bulletTag != enCollisionAttr_Player1_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー2の右足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_RightLeg &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー3の右足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_RightLeg &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー4の右足に当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_RightLeg &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//プレイヤー以外のものに当たった
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Default)
			{
				isHit = true;
			}
			return 0.0f;
		}
		void Hit(int hitPlayerNo, int attackPlayerNo, int attack,float power)
		{
			//弾丸が当たったプレイヤーのHPを減らす
			g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHitPoint(g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint - attack * power);
			//弾が当たったプレイヤーの自然回復までのインターバルを設定する
			g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHealTimer(300);
			//攻撃してきたプレイヤーの座標をセットする
			g_game->GetHUD(hitPlayerNo).SetEnemyPosition(g_game->GetBulletManager().GetPlayer(attackPlayerNo)->GetPosition());
			g_game->GetHUD(hitPlayerNo).SetDamageFlag(true);
			g_game->GetHUD(hitPlayerNo).SetDamageFlagCount(50);
			//プレイヤーの撃った弾が敵に当たった時にヒットマーカーを表示する
			if (g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint > 0)
			{
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetAttackTrue();
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetAttackCount(50);
			}
			//プレイヤーのHPが0以下なら
			if (g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint <= 0)
			{
				//プレイヤーの撃った弾で敵を倒したときにキルマーカーを表示する
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKillTrue();
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKillCount(50);
				//プレイヤーのHPが0以下になったら0にする
				g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHitPoint(0);
				//プレイヤーを死亡状態にする
				g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetDead();
				//攻撃したプレイヤーのキル数を増やす
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKills(g_game->GetBulletManager().GetPlayer(attackPlayerNo)->GetStatus().Kills + 1);
			}

			isHit = true;
		}
	};
}
void BulletController::Init(float radius, float height, const CVector3& position,int tag)
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
	//m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Player1_Bullet);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Player1_Bullet + tag);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);
}

const CVector3& BulletController::Execute(float deltaTime, CVector3& moveSpeed, int attack)
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
		callback.attack = attack;
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
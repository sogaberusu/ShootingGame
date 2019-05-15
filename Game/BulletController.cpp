#include "stdafx.h"
#include "BulletController.h"
#include "Physics/CollisionAttr.h"
#include "Bullet.h"
#include "Game.h"


BulletController::BulletController()
{
}

namespace {
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
	struct SweepResultWall1 : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
												//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			int bulletTag = me->getUserIndex();
			/*if (convexResult.m_hitCollisionObject == me ||
				convexResult.m_hitCollisionObject->getUserIndex() == bulletTag
				) {
				
				return 0.0f;
			}
			isHit = true;*/
			bool isHitPlayer = false;
			//�v���C���[�ƒe�ۂ̓����蔻��
			//�������g�̒e�ۂɓ�����Ȃ��悤�Ƀ^�O�Ŕ��肷��
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1 &&
				bulletTag != enCollisionAttr_Player1_Bullet)
			{
				isHitPlayer = true;
			}
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2 &&
				bulletTag != enCollisionAttr_Player2_Bullet)
			{
				isHitPlayer = true;
			}
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3 &&
				bulletTag != enCollisionAttr_Player3_Bullet)
			{
				isHitPlayer = true;
			}
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4 &&
				bulletTag != enCollisionAttr_Player4_Bullet)
			{
				isHitPlayer = true;
			}
			if (isHitPlayer) {
				//�e�ۂ����������v���C���[�̔ԍ��ƁA�e�ۂ�ł����v���C���[�̔ԍ������߂�B
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHitPoint(g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint -
					g_game->GetBulletManager().GetPlayer(attackPlayerNo)->GetStatus().Attack);
				g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHealTimer(300);
				if (g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint > 0)
				{
					g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetAttackTrue();
				}
				
				if (g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint < 0)
				{
					g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKillTrue();
					g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHitPoint(0);
					g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKills(g_game->GetBulletManager().GetPlayer(attackPlayerNo)->GetStatus().Kills + 1);
				}
		
				isHit = true;
			}
			//�v���C���[�ȊO�̂��̂ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Default)
			{
				isHit = true;
			}
			return 0.0f;
		}
	};
}
void BulletController::Init(float radius, float height, const CVector3& position,int tag)
{
	m_position = position;
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);
	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	//m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Player1_Bullet);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Player1_Bullet + tag);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);
}

const CVector3& BulletController::Execute(float deltaTime, CVector3& moveSpeed)
{
	//���̈ړ���ƂȂ���W���v�Z����B
	CVector3 nextPosition = m_position;
	//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
	CVector3 addPos = moveSpeed;
	addPos *= deltaTime;
	nextPosition += addPos;

	CVector3 originalXZDir = addPos;
	originalXZDir.y = 0.0f;
	originalXZDir.Normalize();
	//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
	{
		//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
		CVector3 addPos;
		addPos.Subtract(nextPosition, m_position);
		CVector3 addPosXZ = addPos;
		addPosXZ.y = 0.0f;
		//�J�v�Z���R���C�_�[�̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
		CVector3 posTmp = m_position;
		posTmp.y += m_height * 0.5f + m_radius + m_height * 0.1f;
		//���C���쐬�B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
		start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
		//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
		end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

		SweepResultWall1 callback;
		callback.me = m_rigidBody.GetBody();
		//�Փˌ��o�B
		g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

		if (callback.isHit) {
			//���������B
			//�ǁB
			m_isDead = true;
			return m_position;
		}
	}
	//XZ�̈ړ��͊m��B
	m_position.x = nextPosition.x;
	m_position.z = nextPosition.z;

	//�ړ��m��B
	m_position = nextPosition;
	btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	return m_position;
}

/*!
* @brief	���S�������Ƃ�ʒm�B
*/
void BulletController::RemoveRigidBoby()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
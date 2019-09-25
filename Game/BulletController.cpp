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
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g
	struct SweepResultWall1 : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
												//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		int attack;								//�U����
		float headPower = 2.0f;					//���ɓ����������̔{��
		float bodyPower = 1.0f;					//�̂ɓ����������̔{��
		float legPower = 0.7f;					//���ɓ����������̔{��
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			int bulletTag = me->getUserIndex();
			bool isHitPlayer = false;
			//�v���C���[�ƒe�ۂ̓����蔻��
			//�������g�̒e�ۂɓ�����Ȃ��悤�Ƀ^�O�Ŕ��肷��
			//�v���C���[1�̓��ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_Head &&
				bulletTag != enCollisionAttr_Player1_Bullet && 
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo,attackPlayerNo,attack, headPower);
			}
			//�v���C���[2�̓��ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_Head &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, headPower);
			}
			//�v���C���[3�̓��ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_Head &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, headPower);
			}
			//�v���C���[4�̓��ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_Head &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Head;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, headPower);
			}
			//�v���C���[1�̓��̂ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_Body &&
				bulletTag != enCollisionAttr_Player1_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//�v���C���[2�̓��̂ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_Body &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//�v���C���[3�̓��̂ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_Body &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//�v���C���[4�̓��̂ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_Body &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_Body;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, bodyPower);
			}
			//�v���C���[1�̍����ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_LeftLeg &&
				bulletTag != enCollisionAttr_Player1_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[2�̍����ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_LeftLeg &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[3�̍����ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_LeftLeg &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[4�̍����ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_LeftLeg &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_LeftLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[1�̉E���ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player1_RightLeg &&
				bulletTag != enCollisionAttr_Player1_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[2�̉E���ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player2_RightLeg &&
				bulletTag != enCollisionAttr_Player2_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[3�̉E���ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player3_RightLeg &&
				bulletTag != enCollisionAttr_Player3_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[4�̉E���ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player4_RightLeg &&
				bulletTag != enCollisionAttr_Player4_Bullet &&
				isHit == false)
			{
				int hitPlayerNo = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Player1_RightLeg;
				int attackPlayerNo = bulletTag - enCollisionAttr_Player1_Bullet;
				Hit(hitPlayerNo, attackPlayerNo, attack, legPower);
			}
			//�v���C���[�ȊO�̂��̂ɓ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Default)
			{
				isHit = true;
			}
			return 0.0f;
		}
		void Hit(int hitPlayerNo, int attackPlayerNo, int attack,float power)
		{
			//�e�ۂ����������v���C���[��HP�����炷
			g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHitPoint(g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint - attack * power);
			//�e�����������v���C���[�̎��R�񕜂܂ł̃C���^�[�o����ݒ肷��
			g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHealTimer(300);
			//�U�����Ă����v���C���[�̍��W���Z�b�g����
			g_game->GetHUD(hitPlayerNo).SetEnemyPosition(g_game->GetBulletManager().GetPlayer(attackPlayerNo)->GetPosition());
			g_game->GetHUD(hitPlayerNo).SetDamageFlag(true);
			g_game->GetHUD(hitPlayerNo).SetDamageFlagCount(50);
			//�v���C���[�̌������e���G�ɓ����������Ƀq�b�g�}�[�J�[��\������
			if (g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint > 0)
			{
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetAttackTrue();
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetAttackCount(50);
			}
			//�v���C���[��HP��0�ȉ��Ȃ�
			if (g_game->GetBulletManager().GetPlayer(hitPlayerNo)->GetStatus().HitPoint <= 0)
			{
				//�v���C���[�̌������e�œG��|�����Ƃ��ɃL���}�[�J�[��\������
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKillTrue();
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKillCount(50);
				//�v���C���[��HP��0�ȉ��ɂȂ�����0�ɂ���
				g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetHitPoint(0);
				//�v���C���[�����S��Ԃɂ���
				g_game->GetBulletManager().GetPlayer(hitPlayerNo)->SetDead();
				//�U�������v���C���[�̃L�����𑝂₷
				g_game->GetBulletManager().GetPlayer(attackPlayerNo)->SetKills(g_game->GetBulletManager().GetPlayer(attackPlayerNo)->GetStatus().Kills + 1);
			}

			isHit = true;
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

const CVector3& BulletController::Execute(float deltaTime, CVector3& moveSpeed, int attack)
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
		callback.attack = attack;
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
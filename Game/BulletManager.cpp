#include "stdafx.h"
#include "BulletManager.h"
#include "Physics/CollisionAttr.h"
#include "Bullet.h"



BulletManager::BulletManager()
{
	for (int i = 0; i < 4; i++)
	{
		m_player[i] = nullptr;
	}
}


BulletManager::~BulletManager()
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Bullet : m_bullet[i]) {
			delete Bullet;
		}
	}
}

Bullet* BulletManager::NewBullet(int PlayerNumber,int Attack)
{
	Bullet* newBullet = new Bullet(m_player[PlayerNumber]->GetHandPos(), PlayerNumber,Attack);
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

//namespace {
//	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
//	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
//	{
//		bool isHit = false;						//�Փ˃t���O�B
//		CVector3 hitPos = CVector3::Zero();		//�Փ˓_�B
//		CVector3 startPos = CVector3::Zero();	//���C�̎n�_�B
//		float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
//		CVector3 hitNormal = CVector3::Zero();	//�Փ˓_�̖@���B
//		btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
//												//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
//		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
//		{
//			if (convexResult.m_hitCollisionObject == me) {
//				//�����ɏՓ˂����Bor �n�ʂɏՓ˂����B
//				return 0.0f;
//			}
//			//�Փ˓_�̖@�������������Ă���B
//			CVector3 hitNormalTmp;
//			hitNormalTmp.Set(convexResult.m_hitNormalLocal);
//			//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
//			float angle = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up())));
//			if (angle >= CMath::PI * 0.3f		//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
//				|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character	//�������̓R���W�����������L�����N�^�Ȃ̂ŕǂƂ݂Ȃ��B
//				) {
//				isHit = true;
//				CVector3 hitPosTmp;
//				hitPosTmp.Set(convexResult.m_hitPointLocal);
//				//��_�Ƃ̋����𒲂ׂ�B
//				CVector3 vDist;
//				vDist.Subtract(hitPosTmp, startPos);
//				vDist.y = 0.0f;
//				float distTmp = vDist.Length();
//				if (distTmp < dist) {
//					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
//					hitPos = hitPosTmp;
//					dist = distTmp;
//					hitNormal = hitNormalTmp;
//				}
//			}
//			return 0.0f;
//		}
//	};
//}
//void BulletManager::Init(float radius, float height, const CVector3& position)
//{
//	m_position = position;
//	//�R���W�����쐬�B
//	m_radius = radius;
//	m_height = height;
//	m_collider.Create(radius, height);
//
//	//���̂��������B
//	RigidBodyInfo rbInfo;
//	rbInfo.collider = &m_collider;
//	rbInfo.mass = 0.0f;
//	m_rigidBody.Create(rbInfo);
//	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
//	//���̂̈ʒu���X�V�B
//	trans.setOrigin(btVector3(position.x, position.y, position.z));
//	//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
//	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
//	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
//	g_physics.AddRigidBody(m_rigidBody);
//}
//
//const CVector3& BulletManager::Execute(float deltaTime, CVector3& moveSpeed,Bullet& bullet)
//{
//	//���̈ړ���ƂȂ���W���v�Z����B
//	CVector3 nextPosition = m_position;
//	//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
//	CVector3 addPos = moveSpeed;
//	addPos *= deltaTime;
//	nextPosition += addPos;
//
//	CVector3 originalXZDir = addPos;
//	originalXZDir.y = 0.0f;
//	originalXZDir.Normalize();
//	//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
//	{
//			//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
//			CVector3 addPos;
//			addPos.Subtract(nextPosition, m_position);
//			CVector3 addPosXZ = addPos;
//			addPosXZ.y = 0.0f;
//			//�J�v�Z���R���C�_�[�̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
//			CVector3 posTmp = m_position;
//			posTmp.y += m_height * 0.5f + m_radius + m_height * 0.1f;
//			//���C���쐬�B
//			btTransform start, end;
//			start.setIdentity();
//			end.setIdentity();
//			//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
//			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
//			//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
//			end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));
//
//			SweepResultWall callback;
//			callback.me = m_rigidBody.GetBody();
//			callback.startPos = posTmp;
//			//�Փˌ��o�B
//			g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
//
//			if (callback.isHit) {
//				//���������B
//				//�ǁB
//				bullet.SetBulletDead();
//			}
//	}
//	//XZ�̈ړ��͊m��B
//	m_position.x = nextPosition.x;
//	m_position.z = nextPosition.z;
//	
//	//�ړ��m��B
//	m_position = nextPosition;
//	btRigidBody* btBody = m_rigidBody.GetBody();
//	//���̂𓮂����B
//	btBody->setActivationState(DISABLE_DEACTIVATION);
//	btTransform& trans = btBody->getWorldTransform();
//	//���̂̈ʒu���X�V�B
//	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
//	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
//	return m_position;
//}
//
///*!
//* @brief	���S�������Ƃ�ʒm�B
//*/
//void BulletManager::RemoveRigidBoby()
//{
//	g_physics.RemoveRigidBody(m_rigidBody);
//}
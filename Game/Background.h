#pragma once
#include "physics/PhysicsStaticObject.h"
#include "graphics/ShadowMap.h"

class Background
{
public:
	Background(CVector3 pos,CQuaternion rot,int mapNo);
	~Background();
	//�`��
	void Draw(Camera& camera);
	//�X�V
	void Update();
	enum enMap
	{
		enContainer,									//�R���e�i
		enTestMap										//�e�X�g�}�b�v
	};
private:
	SkinModel m_model;									//���f��
	PhysicsStaticObject m_phyStaticObject;				//�ÓI�����I�u�W�F�N�g
	CVector3 m_position = CVector3::Zero();             //���f���̍��W
	CQuaternion m_rotation = CQuaternion::Identity();   //��]
};

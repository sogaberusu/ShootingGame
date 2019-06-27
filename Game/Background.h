#pragma once
#include "physics/PhysicsStaticObject.h"
#include "graphics/ShadowMap.h"

class Background
{
public:
	Background(CVector3 pos,CQuaternion rot,int mapNo);
	~Background();
	void Draw(Camera& camera);
	void Update();
private:
	SkinModel m_model;
	PhysicsStaticObject m_phyStaticObject;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
};

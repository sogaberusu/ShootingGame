#pragma once
#include "physics/PhysicsStaticObject.h"
class Background
{
public:
	Background();
	~Background();
	void Draw(Camera& camera);
private:
	SkinModel m_model;
	SkinModel m_model1;
	PhysicsStaticObject m_phyStaticObject;
};

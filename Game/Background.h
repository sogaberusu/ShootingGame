#pragma once
#include "physics/PhysicsStaticObject.h"
#include "graphics/ShadowMap.h"

class Background
{
public:
	Background();
	~Background();
	void Draw(Camera& camera);
	void Update();
private:
	SkinModel m_model;
	PhysicsStaticObject m_phyStaticObject;
};

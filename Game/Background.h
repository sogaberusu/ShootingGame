#pragma once
#include "physics/PhysicsStaticObject.h"
#include "graphics/ShadowMap.h"

class Background
{
public:
	Background();
	~Background();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="camera"></param>
	void Draw(Camera& camera);
	/// <summary>
	/// 
	/// </summary>
	/// <remarks>
	/// </remarks>
	void Update();
private:
	SkinModel m_model;
	PhysicsStaticObject m_phyStaticObject;
};

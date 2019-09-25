#pragma once
#include "physics/PhysicsStaticObject.h"
#include "graphics/ShadowMap.h"

class Background
{
public:
	Background(CVector3 pos,CQuaternion rot,int mapNo);
	~Background();
	//描画
	void Draw(Camera& camera);
	//更新
	void Update();
	enum enMap
	{
		enContainer,									//コンテナ
		enTestMap										//テストマップ
	};
private:
	SkinModel m_model;									//モデル
	PhysicsStaticObject m_phyStaticObject;				//静的物理オブジェクト
	CVector3 m_position = CVector3::Zero();             //モデルの座標
	CQuaternion m_rotation = CQuaternion::Identity();   //回転
};

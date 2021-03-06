/*!
* @brief	グレネードコントローラー。
*/

#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"


/*!
* @brief	グレネードコントローラー。
*/
class GrenadeController {
public:
	GrenadeController() {

	}
	~GrenadeController()
	{
		RemoveRigidBoby();
	}
	/*!
		* @brief	初期化。
		*@param[in]	radius		カプセルコライダーの半径。
		*@param[in]	height		カプセルコライダーの高さ。
		*@param[in]	position	初期位置。
		*/
	void Init(float radius, float height, const CVector3& position, CVector3& moveSpeed);
	/*!
		* @brief	実行。
		*@param[in]	deltaTime		経過時間。単位は秒。
		*@return 移動後のグレネードの座標。
		*/
	const CVector3& Execute(float deltaTime);
	/*!
		* @brief	座標を取得。
		*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	座標を設定。
		*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	* @brief	コライダーを取得。
	*/
	CapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	剛体を取得。
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	剛体を物理エンジンから削除。。
	*/
	void RemoveRigidBoby();
private:
	CVector3 			m_position = CVector3::Zero();	//座標。
	CapsuleCollider		m_collider;						//コライダー。
	float				m_radius = 0.0f;				//剛体の半径
	float				m_height = 0.0f;				//剛体の高さ
	RigidBody			m_rigidBody;					//剛体。
	CVector3			m_moveSpeed = CVector3::Zero(); //速度
};
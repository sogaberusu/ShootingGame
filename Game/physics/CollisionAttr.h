/*!
 * @brief	コリジョン属性
 */
#pragma once

/*!
 * @brief	コリジョン属性の大分類。
 */
enum EnCollisionAttr{
	enCollisionAttr_Default = -1,
	enCollisionAttr_Player1 = 0,		//Player1
	enCollisionAttr_Player2,			//Player2
	enCollisionAttr_Player3,			//Player3
	enCollisionAttr_Player4,			//Player4
	enCollisionAttr_Player1_Bullet,		//Player1の弾丸
	enCollisionAttr_Player2_Bullet,		//Player2の弾丸
	enCollisionAttr_Player3_Bullet,		//Player3の弾丸
	enCollisionAttr_Player4_Bullet,		//Player4の弾丸
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_User,				//以下にユーザー定義のコリジョン属性を設定する。
	
};
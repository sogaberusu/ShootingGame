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
	enCollisionAttr_Player1_Head,		//Player1の頭
	enCollisionAttr_Player2_Head,		//Player2の頭
	enCollisionAttr_Player3_Head,		//Player3の頭
	enCollisionAttr_Player4_Head,		//Player4の頭
	enCollisionAttr_Player1_Body,		//Player1の胴体
	enCollisionAttr_Player2_Body,		//Player2の胴体
	enCollisionAttr_Player3_Body,		//Player3の胴体
	enCollisionAttr_Player4_Body,		//Player4の胴体
	enCollisionAttr_Player1_LeftLeg,	//Player1の左足
	enCollisionAttr_Player2_LeftLeg,	//Player2の左足
	enCollisionAttr_Player3_LeftLeg,	//Player3の左足
	enCollisionAttr_Player4_LeftLeg,	//Player4の左足
	enCollisionAttr_Player1_RightLeg,	//Player1の右足
	enCollisionAttr_Player2_RightLeg,	//Player2の右足
	enCollisionAttr_Player3_RightLeg,	//Player3の右足
	enCollisionAttr_Player4_RightLeg,	//Player4の右足
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_User,				//
	
};
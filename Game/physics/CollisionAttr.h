/*!
 * @brief	�R���W��������
 */
#pragma once

/*!
 * @brief	�R���W���������̑啪�ށB
 */
enum EnCollisionAttr{
	enCollisionAttr_Default = -1,
	enCollisionAttr_Player1 = 0,		//Player1
	enCollisionAttr_Player2,			//Player2
	enCollisionAttr_Player3,			//Player3
	enCollisionAttr_Player4,			//Player4
	enCollisionAttr_Player1_Bullet,		//Player1�̒e��
	enCollisionAttr_Player2_Bullet,		//Player2�̒e��
	enCollisionAttr_Player3_Bullet,		//Player3�̒e��
	enCollisionAttr_Player4_Bullet,		//Player4�̒e��
	enCollisionAttr_Player1_Head,		//Player1�̓�
	enCollisionAttr_Player2_Head,		//Player2�̓�
	enCollisionAttr_Player3_Head,		//Player3�̓�
	enCollisionAttr_Player4_Head,		//Player4�̓�
	enCollisionAttr_Player1_Body,		//Player1�̓���
	enCollisionAttr_Player2_Body,		//Player2�̓���
	enCollisionAttr_Player3_Body,		//Player3�̓���
	enCollisionAttr_Player4_Body,		//Player4�̓���
	enCollisionAttr_Player1_LeftLeg,	//Player1�̍���
	enCollisionAttr_Player2_LeftLeg,	//Player2�̍���
	enCollisionAttr_Player3_LeftLeg,	//Player3�̍���
	enCollisionAttr_Player4_LeftLeg,	//Player4�̍���
	enCollisionAttr_Player1_RightLeg,	//Player1�̉E��
	enCollisionAttr_Player2_RightLeg,	//Player2�̉E��
	enCollisionAttr_Player3_RightLeg,	//Player3�̉E��
	enCollisionAttr_Player4_RightLeg,	//Player4�̉E��
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_User,				//
	
};
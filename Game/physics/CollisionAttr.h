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
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_User,				//�ȉ��Ƀ��[�U�[��`�̃R���W����������ݒ肷��B
	
};
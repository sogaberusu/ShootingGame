#pragma once

//class Minotaur;
//class Goblin;
class Player;

#include "character/CharacterController.h"

class GameCamera
{
public:
	GameCamera(CVector3 camerapos);
	~GameCamera();
	/*void SetPlayer(Minotaur* minotaur)
	{
		m_minotaur = minotaur;
	}
	void SetPlayer(Goblin* goblin)
	{
		m_goblin = goblin;
	}*/
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	void Update();
	void InitViewport(float Width, float Height, float TopLeftX, float TopLeftY)
	{
		m_width = Width;
		m_height = Height;
		m_topLeftX = TopLeftX;
		m_topLeftY = TopLeftY;
	}
	void Seti(int a)
	{
		i = a;
	}
	void StartRender();
	void EndRender();
	void Respawn(int cameraNo,CVector3 position)
	{
		g_camera3D[cameraNo].SetPosition(position);
		g_camera3D[cameraNo].SetTarget({ 0.0f, 200.0f, 0.0f });
		////�����_���王�_�܂ł̃x�N�g����ݒ�B
		m_toCameraPos.Set(g_camera3D[i].GetTarget() - g_camera3D[i].GetPosition());
		////���_���璍���_�܂ł̃x�N�g����ݒ�B
		m_toCameraTarget.Set(g_camera3D[i].GetPosition() - g_camera3D[i].GetTarget());
	}
private:	
	//Minotaur * m_minotaur = nullptr;				//�v���C���[�B
	//Goblin * m_goblin = nullptr;					//�v���C���[�B
	Player *m_player = nullptr;
	CVector3 m_toCameraPos;							//�J�����̃|�W�V����
	CVector3 m_toCameraTarget;						//�J�����̃^�[�Q�b�g
	enum EnCameraType {								//�J�����̏��
		enType_TPS,									//TPS���_
		enType_FPS									//FPS���_
	};
	float m_rStickX;									//�E�X�e�B�b�N��X
	float m_rStickY;									//�E�X�e�B�b�N��Y
	float m_lStickX;									//���X�e�B�b�N��X
	float m_lStickY;									//���X�e�B�b�N��Y

	float m_width = 0;
	float m_height = 0;
	float m_topLeftX = 0;
	float m_topLeftY = 0;

	int i = 0;
};
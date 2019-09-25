#pragma once

class Player;

#include "character/CharacterController.h"

class GameCamera
{
public:
	GameCamera(CVector3 camerapos);
	~GameCamera();
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
	void SetPlayerNo(int No)
	{
		m_playerNo = No;
	}
	void StartRender();
	void EndRender();
	void Respawn(int cameraNo,CVector3 position)
	{
		g_camera3D[cameraNo].SetPosition(position);
		g_camera3D[cameraNo].SetTarget({ 0.0f, 200.0f, 0.0f });
		////�����_���王�_�܂ł̃x�N�g����ݒ�B
		m_toCameraPos.Set(g_camera3D[m_playerNo].GetTarget() - g_camera3D[m_playerNo].GetPosition());
		////���_���璍���_�܂ł̃x�N�g����ݒ�B
		m_toCameraTarget.Set(g_camera3D[m_playerNo].GetPosition() - g_camera3D[m_playerNo].GetTarget());
	}
private:	
	Player *m_player = nullptr;						//�v���C���[
	CVector3 m_toCameraPos;							//�J�����̃|�W�V����
	CVector3 m_toCameraTarget;						//�J�����̃^�[�Q�b�g
	enum EnCameraType {								//�J�����̏��
		enType_TPS,									//TPS���_
		enType_FPS									//FPS���_
	};
	float m_rStickX;								//�E�X�e�B�b�N��X
	float m_rStickY;								//�E�X�e�B�b�N��Y
	float m_lStickX;								//���X�e�B�b�N��X
	float m_lStickY;								//���X�e�B�b�N��Y

	float m_width = 0;								//�r���[�|�[�g�̕�
	float m_height = 0;								//�r���[�|�[�g�̍���
	float m_topLeftX = 0;							//�r���[�|�[�gx�̎n�_
	float m_topLeftY = 0;							//�r���[�|�[�gy�̎n�_

	int m_playerNo = 0;								//�v���C���[�̔ԍ�
};
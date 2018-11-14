#pragma once

class Minotaur;

class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void SetPlayer(Minotaur* minotaur)
	{
		m_minotaur = minotaur;
	}
	void Update();
private:	
	Minotaur * m_minotaur = nullptr;				//�v���C���[�B
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
};
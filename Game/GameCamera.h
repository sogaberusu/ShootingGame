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
	int m_minotaurCameraTypeLastFrame = enType_TPS;	//1�t���[���O�̃~�m�^�E���X�̃J�����^�C�v�B
	enum EnCameraType {								//�J�����̏��
		enType_TPS,									//TPS���_
		enType_FPS									//FPS���_
	};
	float m_rStickX;								//�E�X�e�B�b�N��X
	float m_rStickY;								//�E�X�e�B�b�N��Y
	CVector3 m_minoforward;
	CVector3 m_minopos;
};
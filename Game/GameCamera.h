#pragma once

class Minotaur;
class Goblin;


class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void SetPlayer(Minotaur* minotaur)
	{
		m_minotaur = minotaur;
	}
	void SetPlayer(Goblin* goblin)
	{
		m_goblin = goblin;
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
private:	
	Minotaur * m_minotaur = nullptr;				//�v���C���[�B
	Goblin * m_goblin = nullptr;					//�v���C���[�B
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
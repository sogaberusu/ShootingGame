#pragma once
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include "IScene.h"
#include "Game.h"
class Player;
class Result:public IScene
{
public:
	/// <summary>
	/// �Q�[���I�����ɃQ�[���N���X������炤
	/// </summary>
	/// <param name="gameMode">�v���C���Ă���Q�[�����[�h</param>
	/// <param name="Player1Kills">�v���C���[1�̃L����</param>
	/// <param name="Player2Kills">�v���C���[2�̃L����</param>
	/// <param name="Player3Kills">�v���C���[3�̃L����</param>
	/// <param name="Player4Kills">�v���C���[4�̃L����</param>
	/// <param name="Player1CaptureTime">�v���C���[1�̊����m�ۂ��Ă�������</param>
	/// <param name="Player2CaptureTime">�v���C���[2�̊����m�ۂ��Ă�������</param>
	/// <param name="Player3CaptureTime">�v���C���[3�̊����m�ۂ��Ă�������</param>
	/// <param name="Player4CaptureTime">�v���C���[4�̊����m�ۂ��Ă�������</param>
	Result(int gameMode,int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills,
		float Player1CaptureTime,float Player2CaptureTime, float Player3CaptureTime, float Player4CaptureTime);
	/// <summary>
	/// �Q�[���I�����ɃQ�[���N���X������炤
	/// </summary>
	/// <param name="gameMode">�v���C���Ă���Q�[�����[�h</param>
	/// <param name="Player1Kills">�v���C���[1�̃L����</param>
	/// <param name="Player2Kills">�v���C���[2�̃L����</param>
	/// <param name="Player3Kills">�v���C���[3�̃L����</param>
	/// <param name="Player1CaptureTime">�v���C���[1�̊����m�ۂ��Ă�������</param>
	/// <param name="Player2CaptureTime">�v���C���[2�̊����m�ۂ��Ă�������</param>
	/// <param name="Player3CaptureTime">�v���C���[3�̊����m�ۂ��Ă�������</param>
	Result(int gameMode, int Player1Kills, int Player2Kills, int Player3Kills,
		float Player1CaptureTime, float Player2CaptureTime, float Player3CaptureTime);
	/// <summary>
	/// �Q�[���I�����ɃQ�[���N���X������炤
	/// </summary>
	/// <param name="gameMode">�v���C���Ă���Q�[�����[�h</param>
	/// <param name="Player1Kills">�v���C���[1�̃L����</param>
	/// <param name="Player2Kills">�v���C���[2�̃L����</param>
	/// <param name="Player1CaptureTime">�v���C���[1�̊����m�ۂ��Ă�������</param>
	/// <param name="Player2CaptureTime">�v���C���[2�̊����m�ۂ��Ă�������</param>
	Result(int gameMode, int Player1Kills, int Player2Kills,
		float Player1CaptureTime, float Player2CaptureTime);
	~Result();
	//�A�b�v�f�[�g
	void Update();
	//�h���[
	void Draw();
	//������
	void Init();
private:
	Sprite m_background;					//���U���g��ʂ̔w�i�摜
	Sprite m_1stCrown[PLAYERS];             //��ʂ̉����̉摜
	Sprite m_2ndCrown[PLAYERS];				//��ʂ̉����̉摜
	Sprite m_3rdCrown[PLAYERS];				//�O�ʂ̉����̉摜
	Font m_font;							//�t�H���g
	int m_playerkills[PLAYERS];             //�e�v���C���[�̃L������ۑ����Ă����ϐ�
	float m_playerCaptureTime[PLAYERS];     //�e�v���C���[�̊����m�ۂ��Ă������Ԃ��L�^���Ă����ϐ�
	int m_gameMode;							//���݂̃Q�[�����[�h
	int m_1stKills;							//��ʂ̃L����		
	int m_2ndKills;							//��ʂ̃L����
	int m_3rdKills;							//�O�ʂ̃L����
	float m_1stTime;						//��ʂ̊����m�ۂ��Ă�������
	float m_2ndTime;						//��ʂ̊����m�ۂ��Ă�������
	float m_3rdTime;                        //�O�ʂ̊����m�ۂ��Ă�������
	bool m_1stCrownDrawFlag[PLAYERS] = {};	//��ʂ̉�����N�ɕ`�悷�邩�̃t���O
	bool m_2ndCrownDrawFlag[PLAYERS] = {};	//��ʂ̉�����N�ɕ`�悷�邩�̃t���O
	bool m_3rdCrownDrawFlag[PLAYERS] = {};	//�O�ʂ̉�����N�ɕ`�悷�邩�̃t���O
};
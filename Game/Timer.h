#pragma once
#include "graphics/Font.h"
#include "Player.h"
#include "Game.h"
/// <summary>
/// Timer
/// </summary>
class Timer
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Timer();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Timer();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	void SetPlayer(Player* player,int playerNo)
	{
		m_player[playerNo] = player;
	}
	enum EnPlayer
	{
		enPlayer1,
		enPlayer2,
		enPlayer3,
		enPlayer4
	};
private:
	Font* m_font = nullptr;	//�t�H���g�B
	Player * m_player[PLAYERS];
	CVector4 m_timerColorGray{0.0f,0.0f,0.0f,1.0f};
};
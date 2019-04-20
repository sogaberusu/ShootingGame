#pragma once
#include "graphics/Font.h"
#include "Player.h"
class Game;

/// <summary>
/// HUD
/// </summary>
class HUD
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	HUD();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~HUD();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(int playerNo);
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
	Player * m_player[4];
};
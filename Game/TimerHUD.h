#pragma once
#include "graphics/Font.h"
class Game;

/// <summary>
/// �^�C�}�[HUD
/// </summary>
class TimerHUD
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	TimerHUD();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~TimerHUD();
	/// <summary>
	/// �����ՂŁ[��
	/// </summary>
	//void Update();
private:
	Font* m_fontRender = nullptr;	//�t�H���g�B
	Game* m_game = nullptr;
};
#pragma once
#include "graphics/Font.h"
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
	/// �����ՂŁ[��
	/// </summary>
	void Draw();
private:
	Font* m_font = nullptr;	//�t�H���g�B
};
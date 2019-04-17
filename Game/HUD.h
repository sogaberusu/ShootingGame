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
	/// コンストラクタ。
	/// </summary>
	HUD();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~HUD();
	/// <summary>
	/// あっぷでーと
	/// </summary>
	void Draw();
private:
	Font* m_font = nullptr;	//フォント。
};
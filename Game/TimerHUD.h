#pragma once
#include "graphics/Font.h"
class Game;

/// <summary>
/// タイマーHUD
/// </summary>
class TimerHUD
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	TimerHUD();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~TimerHUD();
	/// <summary>
	/// あっぷでーと
	/// </summary>
	//void Update();
private:
	Font* m_fontRender = nullptr;	//フォント。
	Game* m_game = nullptr;
};
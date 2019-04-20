#include "stdafx.h"
#include "system/system.h"
#include "Title.h"
#include <algorithm>
#include "sound/SoundEngine.h"

IScene* g_currentScene = nullptr;

void UpdateGame()
{
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//物理エンジンの更新。
	g_physics.Update();
	//現在のシーンの更新。
	g_currentScene->Update();
}

void RenderGame()
{
	//描画開始。
	g_graphicsEngine->BegineRender();
	
	//現在のシーンの描画。
	g_currentScene->Draw();
	//g_physics.DebubDrawWorld();

	//描画終了。
	g_graphicsEngine->EndRender();
	
}

void TermnateGame()
{


}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームエンジンの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	CSoundEngine soundEngine;				//サウンドエンジン。
	soundEngine.Init();
	//タイトルシーンの作成。
	g_currentScene = new Title;
	//g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//ゲームの更新。
		UpdateGame();
		//音楽データの更新
		soundEngine.Update();
		//ゲームの描画処理。
		RenderGame();
	}
	//ゲームの終了処理
	TermnateGame();
}
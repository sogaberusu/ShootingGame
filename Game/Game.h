#pragma once

#include "IScene.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"
#include "StoneManager.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "graphics/PostEffect.h"
//ゲームクラス。
class Game : public IScene
{
public:
	enum EnCameraType {
		enCamera_TPS,
		enCamera_FPS
	};
	/*!
	* @brief	コンストラクタ。
	*/
	Game();
	/*!
	* @brief	デストラクタ
	*/
	~Game();
	/*!
	* @brief	更新。
	*/
	void Update()override;
	/*!
	* @brief	描画。
	*/
	void Draw()override;

	void DrawShadowMap();

	StoneManager& GetStoneManager()
	{
		return m_stoneManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
private:
	//Minotaur m_minotaur[4];				//プレイヤー
	Player m_player[4];
	Level m_level;						//レベルを初期化。
	GameCamera m_gameCamera[4];
	Background m_bg;
	//Goblin m_goblin;
	//Orc m_orc;
	StoneManager m_stoneManager;
	EnCameraType m_cameratype = enCamera_FPS;
	bool m_dorwflag;
	int i = 0;
	Sky m_sky;	//空。
	//RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	PostEffect m_postEffect;				//ポストエフェクト。
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;

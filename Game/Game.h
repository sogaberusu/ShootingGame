#pragma once

#include "IScene.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"
#include "StoneManager.h"
#include "BulletManager.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "graphics/PostEffect.h"
#include "HUD.h"
//ゲームクラス。
class Game : public IScene
{
public:
	enum EnCameraType {
		enCamera_TPS,
		enCamera_FPS
	};
	struct SRespawn
	{
		CVector3 PlayerPosition;
		CQuaternion PlayerRotation;
		CVector3 CameraPosition;
	};
	struct SViewport
	{
		float Width;
		float Height;
		float TopLeftX;
		float TopLeftY;
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
	BulletManager& GetBulletManager()
	{
		return m_bulletManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	SRespawn GetPlayerRespawn(int playerNo,int random)
	{
		m_gameCamera[playerNo]->Respawn(playerNo, m_respawn[random].CameraPosition);
		/*delete m_gameCamera[playerNo];
		m_gameCamera[playerNo] = new GameCamera(m_respawn[random].CameraPosition);
		m_gameCamera[playerNo]->InitViewport(m_viewport->Width, m_viewport->Height, m_viewport->TopLeftX, m_viewport->TopLeftY);
		m_gameCamera[playerNo]->SetPlayer(&m_player[playerNo]);
		m_gameCamera[playerNo]->Seti(playerNo);
		*/
		return m_respawn[random];
	}
	/// <summary>
	/// ゲームの残り時間を取得を取得。
	/// </summary>
	/// <returns></returns>
	float GetRestTime() const
	{
		return m_restTimer;
	}
private:
	//Minotaur m_minotaur[4];				//プレイヤー
	Player m_player[4];
	//Level m_level;						//レベルを初期化。
	GameCamera* m_gameCamera[4];
	Background* m_bg;
	//Goblin m_goblin;
	//Orc m_orc;
	StoneManager m_stoneManager;
	BulletManager m_bulletManager;
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
	Level m_level;
	SRespawn m_respawn[4];
	SViewport m_viewport[4];
	float m_restTimer = 90.0f;									//ゲームの残り時間。単位：秒。
	HUD m_timer;
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;

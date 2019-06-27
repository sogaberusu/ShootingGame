#pragma once

#include "IScene.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "BulletManager.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "Timer.h"
#include "HUD.h"
#include "Result.h"
#include "Effect.h"
#include "M4A1.h"
#include "MP5.h"
#include "Benelli_M4.h"
#include "M110.h"
#include "GrenadeManager.h"
#include "graphics/Font.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Flag.h"
//ゲームクラス。
enum EnGameType {
		enGame_DM,
		enGame_CTF
	};
class Game : public IScene
{
public:
	enum EnCameraType {
		enCamera_TPS,						//TPS
		enCamera_FPS						//FPS
	};
	
	struct SRespawn
	{
		CVector3 PlayerPosition;			//プレイヤーの座標
		CQuaternion PlayerRotation;			//プレイヤーの回転
		CVector3 CameraPosition;			//カメラのポジション
	};
	/*!
	* @brief	コンストラクタ。
	*/
	Game(int gameMode,int mapNo);
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

	/// <summary>
	/// 影の描画
	/// </summary>
	void DrawShadowMap();

	BulletManager& GetBulletManager()
	{
		return m_bulletManager;
	}
	GrenadeManager&GetGrenadeManager()
	{
		return m_grenadeManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	SRespawn GetPlayerRespawn(int playerNo,int random)
	{
		m_gameCamera[playerNo]->Respawn(playerNo, m_respawn[random].CameraPosition);
		return m_respawn[random];
	}
	/// <summary>
	/// ゲームの残り時間を取得を取得。
	/// </summary>
	float GetRestTime() const
	{
		return m_restTimer;
	}
	Effect &GetMuzzleFlasheEffect(int playerNo)
	{
		return m_muzzleflasheffect[playerNo];
	}
	Effect &GetExplosionEffect(int playerNo)
	{
		return m_explosioneffect[playerNo];
	}
	M4A1 &GetM4A1(int playerNo)
	{
		return m_m4a1[playerNo];
	}
	HUD &GetHUD(int playerNo)
	{
		return m_hud[playerNo];
	}
	void SetPlayerWeapon()
	{
		for (int i = 0; i < 4; i++)
		{
			m_player[i]->SetWeapon(enWeapon_M4A1);
		}
	}
private:
	Player *m_player[4];												//プレイヤー
	GameCamera* m_gameCamera[4];										//ゲームカメラ
	Background* m_background;											//背景
	BulletManager m_bulletManager;										//弾
	EnCameraType m_cameratype = enCamera_FPS;							//カメラの状態
	bool m_drawflag;													//プレイヤーを描画するか?
	Sky m_sky;															//空。
	Sprite m_copyMainRtToFrameBufferSprite;								//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファのビューポート。
	Level m_level;														//レベル
	SRespawn m_respawn[4];												//リスポーンの
	float m_restTimer = 90.0f;											//ゲームの残り時間。単位：秒。
	float m_startTimer = 3.0f;											//ゲームの開始時間。単位：秒。
	Timer m_timer;														//残り時間を描画する
	HUD m_hud[4];														
	M4A1 m_m4a1[4];														//fps視点の時のモデル
	MP5 m_mp5[4];														//fps視点の時のモデル
	M110 m_m110[4];
	Benelli_M4 m_benelliM4[4];
	Effect m_muzzleflasheffect[4];
	Effect m_explosioneffect[4];
	GrenadeManager m_grenadeManager;
	Font m_font;
	bool m_weaponflag = true;
	bool m_endflag = false;
	bool m_transitionflag = false;
	bool m_waitflag = true;
	bool m_endSoundflag = true;
	CSoundSource m_startSound;
	CSoundSource m_endSound;
	Flag m_flag;
	
	int m_gameMode;
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;

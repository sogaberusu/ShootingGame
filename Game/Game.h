#pragma once
/// <summary>
/// プレイ人数2～4を想定
/// </summary>
#define PLAYERS 4
#include "IScene.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "Result.h"
#include "Effect.h"
#include "M4A1.h"
#include "MP5.h"
#include "Benelli_M4.h"
#include "M110.h"
#include "graphics/Font.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
class HUD;
class Flag;
class Timer;
class GrenadeManager;
class BulletManager;
//ゲームモード
enum EnGameType {
		enGame_DM,
		enGame_CTF
	};
//プレイヤー番号
enum EnPlayers {
	enPlayer1,
	enPlayer2,
	enPlayer3,
	enPlayer4,
	enPlayerNum
};
//ゲームクラス。
class Game : public IScene
{
public:
	/// <summary>
	/// カメラの状態
	/// </summary>
	enum EnCameraType {
		enCamera_TPS,						//TPS
		enCamera_FPS						//FPS
	};
	/// <summary>
	/// 生き返るときに使う
	/// </summary>
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
	//バレットマネージャーを取得
	BulletManager& GetBulletManager()
	{
		return *m_bulletManager;
	}
	//グレネードマネージャーを取得
	GrenadeManager& GetGrenadeManager()
	{
		return *m_grenadeManager;
	}
	//マズルフラッシュのエフェクトを取得
	Effect &GetMuzzleFlasheEffect(int playerNo)
	{
		return m_muzzleflasheffect[playerNo];
	}
	//グレネードの爆発のエフェクトを取得
	Effect &GetExplosionEffect(int playerNo)
	{
		return m_explosioneffect[playerNo];
	}
	//画面に表示するものを取得
	HUD &GetHUD(int playerNo)
	{
		return *m_hud[playerNo];
	}
	//今のカメラの状態を記憶する
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	/// <summary>
	/// 生き返る時に使う
	/// </summary>
	/// <param name="playerNo">倒されたプレイヤー番号</param>
	/// <param name="random">0～3までのランダムな値が入る</param>
	/// <returns>生き返る時に使う構造体を返す</returns>
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
	
	//プレイヤーに銃を持たせる
	void SetPlayerWeapon()
	{
		for (int i = 0; i < PLAYERS; i++)
		{
			m_player[i]->SetWeapon(enWeapon_M4A1);
		}
	}
private:
	Player *m_player[PLAYERS];											//プレイヤー
	GameCamera* m_gameCamera[PLAYERS];									//ゲームカメラ
	Background* m_background;											//背景
	BulletManager* m_bulletManager;										//弾
	EnCameraType m_cameratype = enCamera_FPS;							//カメラの状態
	bool m_drawflag;													//プレイヤーを描画するか?
	Sky m_sky;															//空。
	Sprite m_copyMainRtToFrameBufferSprite;								//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファのビューポート。
	Level m_level;														//レベル
	SRespawn m_respawn[enPlayerNum];									//リスポーンの時に使う構造体
	float m_restTimer = 180.0f;											//ゲームの残り時間。単位：秒。
	float m_startTimer = 3.0f;											//ゲームの開始時間。単位：秒。
	Timer* m_timer;														//残り時間を描画する
	HUD* m_hud[PLAYERS];												//画面に表示される情報
	M4A1 m_m4a1[PLAYERS];												//モデル
	MP5 m_mp5[PLAYERS];													//モデル
	M110 m_m110[PLAYERS];												//モデル
	Benelli_M4 m_benelliM4[PLAYERS];		 							//モデル
	Effect m_muzzleflasheffect[PLAYERS];								//マズルフラッシュのエフェクト
	Effect m_explosioneffect[PLAYERS];									//グレネードの爆発のエフェクト
	GrenadeManager* m_grenadeManager;									//グレネード
	Font m_font;														//フォント
	bool m_weaponflag = true;											//プレイヤーに銃を持たせるフラグ
	bool m_endflag = false;												//残り時間が0になったかのフラグ
	bool m_transitionflag = false;										//リザルト画面に遷移するためのフラグ
	bool m_waitflag = true;												//ゲームが始まって少しの間止めるフラグ
	bool m_endSoundflag = true;											//ゲーム終了の音を鳴らすフラグ
	CSoundSource m_startSound;											//ゲーム開始の笛の音
	CSoundSource m_endSound;											//ゲーム終了の笛の音
	Flag* m_flag;														//キャプチャーザフラッグで使うの旗
	int m_gameMode;                                                     //セレクト画面で選択されたゲームモードを入れておくための変数
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;

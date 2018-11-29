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

	StoneManager& GetStoneManager()
	{
		return m_stoneManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
private:
	Minotaur m_minotaur[4];				//プレイヤー
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
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;

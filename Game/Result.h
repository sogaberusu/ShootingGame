#pragma once
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include "IScene.h"
#include "Game.h"
class Player;
class Result:public IScene
{
public:
	/// <summary>
	/// ゲーム終了時にゲームクラスからもらう
	/// </summary>
	/// <param name="gameMode">プレイしているゲームモード</param>
	/// <param name="Player1Kills">プレイヤー1のキル数</param>
	/// <param name="Player2Kills">プレイヤー2のキル数</param>
	/// <param name="Player3Kills">プレイヤー3のキル数</param>
	/// <param name="Player4Kills">プレイヤー4のキル数</param>
	/// <param name="Player1CaptureTime">プレイヤー1の旗を確保していた時間</param>
	/// <param name="Player2CaptureTime">プレイヤー2の旗を確保していた時間</param>
	/// <param name="Player3CaptureTime">プレイヤー3の旗を確保していた時間</param>
	/// <param name="Player4CaptureTime">プレイヤー4の旗を確保していた時間</param>
	Result(int gameMode,int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills,
		float Player1CaptureTime,float Player2CaptureTime, float Player3CaptureTime, float Player4CaptureTime);
	/// <summary>
	/// ゲーム終了時にゲームクラスからもらう
	/// </summary>
	/// <param name="gameMode">プレイしているゲームモード</param>
	/// <param name="Player1Kills">プレイヤー1のキル数</param>
	/// <param name="Player2Kills">プレイヤー2のキル数</param>
	/// <param name="Player3Kills">プレイヤー3のキル数</param>
	/// <param name="Player1CaptureTime">プレイヤー1の旗を確保していた時間</param>
	/// <param name="Player2CaptureTime">プレイヤー2の旗を確保していた時間</param>
	/// <param name="Player3CaptureTime">プレイヤー3の旗を確保していた時間</param>
	Result(int gameMode, int Player1Kills, int Player2Kills, int Player3Kills,
		float Player1CaptureTime, float Player2CaptureTime, float Player3CaptureTime);
	/// <summary>
	/// ゲーム終了時にゲームクラスからもらう
	/// </summary>
	/// <param name="gameMode">プレイしているゲームモード</param>
	/// <param name="Player1Kills">プレイヤー1のキル数</param>
	/// <param name="Player2Kills">プレイヤー2のキル数</param>
	/// <param name="Player1CaptureTime">プレイヤー1の旗を確保していた時間</param>
	/// <param name="Player2CaptureTime">プレイヤー2の旗を確保していた時間</param>
	Result(int gameMode, int Player1Kills, int Player2Kills,
		float Player1CaptureTime, float Player2CaptureTime);
	~Result();
	//アップデート
	void Update();
	//ドロー
	void Draw();
	//初期化
	void Init();
private:
	Sprite m_background;					//リザルト画面の背景画像
	Sprite m_1stCrown[PLAYERS];             //一位の王冠の画像
	Sprite m_2ndCrown[PLAYERS];				//二位の王冠の画像
	Sprite m_3rdCrown[PLAYERS];				//三位の王冠の画像
	Font m_font;							//フォント
	int m_playerkills[PLAYERS];             //各プレイヤーのキル数を保存しておく変数
	float m_playerCaptureTime[PLAYERS];     //各プレイヤーの旗を確保していた時間を記録しておく変数
	int m_gameMode;							//現在のゲームモード
	int m_1stKills;							//一位のキル数		
	int m_2ndKills;							//二位のキル数
	int m_3rdKills;							//三位のキル数
	float m_1stTime;						//一位の旗を確保していた時間
	float m_2ndTime;						//二位の旗を確保していた時間
	float m_3rdTime;                        //三位の旗を確保していた時間
	bool m_1stCrownDrawFlag[PLAYERS] = {};	//一位の王冠を誰に描画するかのフラグ
	bool m_2ndCrownDrawFlag[PLAYERS] = {};	//二位の王冠を誰に描画するかのフラグ
	bool m_3rdCrownDrawFlag[PLAYERS] = {};	//三位の王冠を誰に描画するかのフラグ
};
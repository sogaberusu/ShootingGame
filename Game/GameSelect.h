#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"

class GameSelect : public IScene
{
public:
	GameSelect();
	~GameSelect();
	//更新
	void Update() override;
	//描画
	void Draw() override;
	
private:
	Sprite m_background;									//背景の画像
	Sprite m_rightselect;									//右向きの三角の画像	
	Sprite m_leftselect;									//左向きの三角の画像
	Sprite m_startButton;									//スタートボタンの画像
	Font m_font;											//フォント
	CVector2 m_fontDMPos = { -100.0f,100.0f };				//フォント「デスマッチ」を表示する座標
	CVector2 m_fontCTFPos = { 1000.0f,100.0f };				//フォント「キャプチャーザフラッグ」を表示する座標
	CVector2 m_fontContainerPos = { -100.0f,-170.0f };		//フォント「コンテナマップ」を表示する座標
	CVector2 m_fontTestMapPos = { 1000.0f,-170.0f };		//フォント「テストマップ」を表示する座標
	bool m_leftMoveflag = false;							//左に移動させ続けるフラグ
	bool m_rightMoveflag = false;							//右に移動させ続けるフラグ
	enum EnGameType {
		enGame_DM,											//デスマッチ
		enGame_CTF											//キャプチャーザフラッグ
	};
	EnGameType m_gametype = enGame_DM;						//プレイするゲームモード
	enum EnMapType {
		enMap_Container,									//コンテナマップ
		enMap_Test											//テストマップ
	};
	EnMapType m_maptype = enMap_Container;					//プレイするマップ
	CVector4 Black = { 0.0f,0.0f,0.0f,1.0f };				//黒
	CVector4 Red = { 256.0f,0.0f,0.0f,1.0f };				//赤
	CVector4 m_gameTypeFontColor = Black;					//ゲームルールのフォントの色
	CVector4 m_stageFontColor = Black;						//ステージのフォントの色
	CVector4 m_gameStartFontColor = Black;					//スタートのフォントの色
	enum EnState {
		enState_GameType,									//ゲームルール
		enState_GameMap,									//マップ選択
		enState_GameStart,									//ゲーム開始
	};
	EnState m_state = enState_GameType;						//現在のカーソルの位置
};
#pragma once
#include "Player.h"
#include "Game.h"
class Flag
{
public:
	Flag();
	~Flag();
	//描画
	void Draw(Camera& camera);
	//更新
	void Update();
	//プレイヤーのインスタンスを設定する
	void SetInstance(Player *player, int PlayerNumber)
	{
		m_player[PlayerNumber] = player;
	}
private:
	SkinModel m_model;										//モデル
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	Player* m_player[PLANES];								//プレイヤーのインスタンス
	int m_playerNo = enPlayer1;								//プレイヤー番号		
};
#pragma once

//class Minotaur;
//class Goblin;
class Player;

#include "character/CharacterController.h"

class GameCamera
{
public:
	GameCamera(CVector3 camerapos);
	~GameCamera();
	/*void SetPlayer(Minotaur* minotaur)
	{
		m_minotaur = minotaur;
	}
	void SetPlayer(Goblin* goblin)
	{
		m_goblin = goblin;
	}*/
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	void Update();
	void InitViewport(float Width, float Height, float TopLeftX, float TopLeftY)
	{
		m_width = Width;
		m_height = Height;
		m_topLeftX = TopLeftX;
		m_topLeftY = TopLeftY;
	}
	void Seti(int a)
	{
		i = a;
	}
	void StartRender();
	void EndRender();
	void Respawn(int cameraNo,CVector3 position)
	{
		g_camera3D[cameraNo].SetPosition(position);
		g_camera3D[cameraNo].SetTarget({ 0.0f, 200.0f, 0.0f });
		////注視点から視点までのベクトルを設定。
		m_toCameraPos.Set(g_camera3D[i].GetTarget() - g_camera3D[i].GetPosition());
		////視点から注視点までのベクトルを設定。
		m_toCameraTarget.Set(g_camera3D[i].GetPosition() - g_camera3D[i].GetTarget());
	}
private:	
	//Minotaur * m_minotaur = nullptr;				//プレイヤー。
	//Goblin * m_goblin = nullptr;					//プレイヤー。
	Player *m_player = nullptr;
	CVector3 m_toCameraPos;							//カメラのポジション
	CVector3 m_toCameraTarget;						//カメラのターゲット
	enum EnCameraType {								//カメラの状態
		enType_TPS,									//TPS視点
		enType_FPS									//FPS視点
	};
	float m_rStickX;									//右スティックのX
	float m_rStickY;									//右スティックのY
	float m_lStickX;									//左スティックのX
	float m_lStickY;									//左スティックのY

	float m_width = 0;
	float m_height = 0;
	float m_topLeftX = 0;
	float m_topLeftY = 0;

	int i = 0;
};
#pragma once

class Minotaur;
class Goblin;


class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void SetPlayer(Minotaur* minotaur)
	{
		m_minotaur = minotaur;
	}
	void SetPlayer(Goblin* goblin)
	{
		m_goblin = goblin;
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
private:	
	Minotaur * m_minotaur = nullptr;				//プレイヤー。
	Goblin * m_goblin = nullptr;					//プレイヤー。
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
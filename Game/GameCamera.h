#pragma once

class Minotaur;

class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void SetPlayer(Minotaur* minotaur)
	{
		m_minotaur = minotaur;
	}
	void Update();
private:	
	Minotaur * m_minotaur = nullptr;				//プレイヤー。
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
};
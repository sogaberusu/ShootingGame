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
	int m_minotaurCameraTypeLastFrame = enType_TPS;	//1フレーム前のミノタウルスのカメラタイプ。
	enum EnCameraType {								//カメラの状態
		enType_TPS,									//TPS視点
		enType_FPS									//FPS視点
	};
	float m_rStickX;								//右スティックのX
	float m_rStickY;								//右スティックのY
	CVector3 m_minoforward;
	CVector3 m_minopos;
};
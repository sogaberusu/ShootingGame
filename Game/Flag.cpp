#include "stdafx.h"
#include "Flag.h"
#include "Physics/CollisionAttr.h"

Flag::Flag()
{
	m_model.Init(L"Assets/modelData/Flag.cmo");

	//初期化
	for (int PlayerNumber = 0; PlayerNumber < PLAYERS; PlayerNumber++)
	{
		m_player[PlayerNumber] = nullptr;
	}

}


Flag::~Flag()
{
}

void Flag::Update()
{
	

	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);

		for (int PlayerNumber = 0; PlayerNumber < PLAYERS; PlayerNumber++)
		{
			if (m_player[PlayerNumber]->GetIsFlag() == false )
			{
				//距離判定
				CVector3 pos;
				pos = m_position - m_player[PlayerNumber]->GetPosition();
				float len = pos.Length();
				if (len < 30.0f)
				{
					m_player[PlayerNumber]->SetIsFlag(true);

					m_playerNo = PlayerNumber;
				}
			}
			else if(m_player[PlayerNumber]->GetDeadFlag() == false)
			{
				m_player[m_playerNo]->SetCaptureTime(m_player[m_playerNo]->GetStatus().CaptureTime + 0.01f);
				m_position = m_player[m_playerNo]->GetPosition();
				m_position -= m_player[m_playerNo]->GetForward() * 15.0f;
				m_rotation = m_player[m_playerNo]->GetRotation();
			}
			
		}
	

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Flag::Draw(Camera& camera)
{
	m_model.Draw(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		enSilhouetteDraw
	);
	
	m_model.Draw(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		enNormalDraw
	);
}
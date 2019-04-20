#include "stdafx.h"
#include "HUD.h"
#include "Game.h"


HUD::HUD()
{	
	m_font = new Font;
}

HUD::~HUD()
{
}

void HUD::Draw(int playerNo)
{
	float restTime = g_game->GetRestTime();
	//restTime�𕪂ƕb�ɕ�����B�B
	/*float min, sec;
	min = restTime / 60.0f;
	sec = fmod(restTime, 60.0f);*/
	wchar_t time[256];
	//swprintf(time, L"�c�莞�� %.f:%02.f", min, sec);
	swprintf(time, L"�c�莞�� %.f�b",restTime);

	m_font->BeginDraw();
	
	m_font->Draw(time, { -640.0f, 360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);

	m_font->EndDraw();
}
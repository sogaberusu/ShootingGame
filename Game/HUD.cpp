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

void HUD::Draw()
{
	float restTime = g_game->GetRestTime();
	//restTime�𕪂ƕb�ɕ�����B�B
	float min, sec;
	min = restTime / 60.0f;
	sec = fmod(restTime, 60.0f);

	wchar_t text[256];
	swprintf(text, L"�c�莞�� %.f:%02.f", min, sec);
	m_font->BeginDraw();
	m_font->Draw(text, { -640.0f, 360.0f }, {0.0f,0.0f,0.0f,1.0f},0.0f,0.5f);
	m_font->EndDraw();
}
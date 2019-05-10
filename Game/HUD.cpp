#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);
}
#include "stdafx.h"
#include "HUDCamera.h"


HUDCamera::HUDCamera()
{
}


HUDCamera::~HUDCamera()
{
}

void HUDCamera::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);
}
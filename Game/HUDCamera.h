#pragma once
class HUDCamera
{
public:
	HUDCamera();
	~HUDCamera();
	void InitViewport(float Width, float Height, float TopLeftX, float TopLeftY)
	{
		m_width = Width;
		m_height = Height;
		m_topLeftX = TopLeftX;
		m_topLeftY = TopLeftY;
	}
	void SetCameraNo(int No)
	{
		cameraNo = No;
	}
	void StartRender();
private:
	float m_width = 0;
	float m_height = 0;
	float m_topLeftX = 0;
	float m_topLeftY = 0;

	int cameraNo;
};


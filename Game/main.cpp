#include "stdafx.h"
#include "system/system.h"
#include "Title.h"
#include <algorithm>
#include "sound/SoundEngine.h"

IScene* g_currentScene = nullptr;

void UpdateGame()
{
	//�Q�[���p�b�h�̍X�V�B	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//�����G���W���̍X�V�B
	g_physics.Update();
	//���݂̃V�[���̍X�V�B
	g_currentScene->Update();
}

void RenderGame()
{
	//�`��J�n�B
	g_graphicsEngine->BegineRender();
	
	//���݂̃V�[���̕`��B
	g_currentScene->Draw();
	//g_physics.DebubDrawWorld();

	//�`��I���B
	g_graphicsEngine->EndRender();
	
}

void TermnateGame()
{


}

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���G���W���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	CSoundEngine soundEngine;				//�T�E���h�G���W���B
	soundEngine.Init();
	//�^�C�g���V�[���̍쐬�B
	g_currentScene = new Title;
	//g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�Q�[���̍X�V�B
		UpdateGame();
		//���y�f�[�^�̍X�V
		soundEngine.Update();
		//�Q�[���̕`�揈���B
		RenderGame();
	}
	//�Q�[���̏I������
	TermnateGame();
}
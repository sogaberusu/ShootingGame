#pragma once

#include "IScene.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"
#include "StoneManager.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "graphics/PostEffect.h"
//�Q�[���N���X�B
class Game : public IScene
{
public:
	enum EnCameraType {
		enCamera_TPS,
		enCamera_FPS
	};
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Game();
	/*!
	* @brief	�f�X�g���N�^
	*/
	~Game();
	/*!
	* @brief	�X�V�B
	*/
	void Update()override;
	/*!
	* @brief	�`��B
	*/
	void Draw()override;

	void DrawShadowMap();

	StoneManager& GetStoneManager()
	{
		return m_stoneManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
private:
	//Minotaur m_minotaur[4];				//�v���C���[
	Player m_player[4];
	Level m_level;						//���x�����������B
	GameCamera m_gameCamera[4];
	Background m_bg;
	//Goblin m_goblin;
	//Orc m_orc;
	StoneManager m_stoneManager;
	EnCameraType m_cameratype = enCamera_FPS;
	bool m_dorwflag;
	int i = 0;
	Sky m_sky;	//��B
	//RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	PostEffect m_postEffect;				//�|�X�g�G�t�F�N�g�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;

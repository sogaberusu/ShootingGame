#pragma once

#include "IScene.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"
#include "StoneManager.h"
#include "BulletManager.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "graphics/PostEffect.h"
#include "HUD.h"
//�Q�[���N���X�B
class Game : public IScene
{
public:
	enum EnCameraType {
		enCamera_TPS,
		enCamera_FPS
	};
	struct SRespawn
	{
		CVector3 PlayerPosition;
		CQuaternion PlayerRotation;
		CVector3 CameraPosition;
	};
	struct SViewport
	{
		float Width;
		float Height;
		float TopLeftX;
		float TopLeftY;
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
	BulletManager& GetBulletManager()
	{
		return m_bulletManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	SRespawn GetPlayerRespawn(int playerNo,int random)
	{
		m_gameCamera[playerNo]->Respawn(playerNo, m_respawn[random].CameraPosition);
		/*delete m_gameCamera[playerNo];
		m_gameCamera[playerNo] = new GameCamera(m_respawn[random].CameraPosition);
		m_gameCamera[playerNo]->InitViewport(m_viewport->Width, m_viewport->Height, m_viewport->TopLeftX, m_viewport->TopLeftY);
		m_gameCamera[playerNo]->SetPlayer(&m_player[playerNo]);
		m_gameCamera[playerNo]->Seti(playerNo);
		*/
		return m_respawn[random];
	}
	/// <summary>
	/// �Q�[���̎c�莞�Ԃ��擾���擾�B
	/// </summary>
	/// <returns></returns>
	float GetRestTime() const
	{
		return m_restTimer;
	}
private:
	//Minotaur m_minotaur[4];				//�v���C���[
	Player m_player[4];
	//Level m_level;						//���x�����������B
	GameCamera* m_gameCamera[4];
	Background* m_bg;
	//Goblin m_goblin;
	//Orc m_orc;
	StoneManager m_stoneManager;
	BulletManager m_bulletManager;
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
	Level m_level;
	SRespawn m_respawn[4];
	SViewport m_viewport[4];
	float m_restTimer = 90.0f;									//�Q�[���̎c�莞�ԁB�P�ʁF�b�B
	HUD m_timer;
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;

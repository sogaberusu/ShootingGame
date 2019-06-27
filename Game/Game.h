#pragma once

#include "IScene.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "BulletManager.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "Timer.h"
#include "HUD.h"
#include "Result.h"
#include "Effect.h"
#include "M4A1.h"
#include "MP5.h"
#include "Benelli_M4.h"
#include "M110.h"
#include "GrenadeManager.h"
#include "graphics/Font.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Flag.h"
//�Q�[���N���X�B
enum EnGameType {
		enGame_DM,
		enGame_CTF
	};
class Game : public IScene
{
public:
	enum EnCameraType {
		enCamera_TPS,						//TPS
		enCamera_FPS						//FPS
	};
	
	struct SRespawn
	{
		CVector3 PlayerPosition;			//�v���C���[�̍��W
		CQuaternion PlayerRotation;			//�v���C���[�̉�]
		CVector3 CameraPosition;			//�J�����̃|�W�V����
	};
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Game(int gameMode,int mapNo);
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

	/// <summary>
	/// �e�̕`��
	/// </summary>
	void DrawShadowMap();

	BulletManager& GetBulletManager()
	{
		return m_bulletManager;
	}
	GrenadeManager&GetGrenadeManager()
	{
		return m_grenadeManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	SRespawn GetPlayerRespawn(int playerNo,int random)
	{
		m_gameCamera[playerNo]->Respawn(playerNo, m_respawn[random].CameraPosition);
		return m_respawn[random];
	}
	/// <summary>
	/// �Q�[���̎c�莞�Ԃ��擾���擾�B
	/// </summary>
	float GetRestTime() const
	{
		return m_restTimer;
	}
	Effect &GetMuzzleFlasheEffect(int playerNo)
	{
		return m_muzzleflasheffect[playerNo];
	}
	Effect &GetExplosionEffect(int playerNo)
	{
		return m_explosioneffect[playerNo];
	}
	M4A1 &GetM4A1(int playerNo)
	{
		return m_m4a1[playerNo];
	}
	HUD &GetHUD(int playerNo)
	{
		return m_hud[playerNo];
	}
	void SetPlayerWeapon()
	{
		for (int i = 0; i < 4; i++)
		{
			m_player[i]->SetWeapon(enWeapon_M4A1);
		}
	}
private:
	Player *m_player[4];												//�v���C���[
	GameCamera* m_gameCamera[4];										//�Q�[���J����
	Background* m_background;											//�w�i
	BulletManager m_bulletManager;										//�e
	EnCameraType m_cameratype = enCamera_FPS;							//�J�����̏��
	bool m_drawflag;													//�v���C���[��`�悷�邩?
	Sky m_sky;															//��B
	Sprite m_copyMainRtToFrameBufferSprite;								//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�̃r���[�|�[�g�B
	Level m_level;														//���x��
	SRespawn m_respawn[4];												//���X�|�[����
	float m_restTimer = 90.0f;											//�Q�[���̎c�莞�ԁB�P�ʁF�b�B
	float m_startTimer = 3.0f;											//�Q�[���̊J�n���ԁB�P�ʁF�b�B
	Timer m_timer;														//�c�莞�Ԃ�`�悷��
	HUD m_hud[4];														
	M4A1 m_m4a1[4];														//fps���_�̎��̃��f��
	MP5 m_mp5[4];														//fps���_�̎��̃��f��
	M110 m_m110[4];
	Benelli_M4 m_benelliM4[4];
	Effect m_muzzleflasheffect[4];
	Effect m_explosioneffect[4];
	GrenadeManager m_grenadeManager;
	Font m_font;
	bool m_weaponflag = true;
	bool m_endflag = false;
	bool m_transitionflag = false;
	bool m_waitflag = true;
	bool m_endSoundflag = true;
	CSoundSource m_startSound;
	CSoundSource m_endSound;
	Flag m_flag;
	
	int m_gameMode;
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;

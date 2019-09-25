#pragma once
/// <summary>
/// �v���C�l��2�`4��z��
/// </summary>
#define PLAYERS 4
#include "IScene.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Sky.h"
#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "graphics/ShadowMap.h"
#include "Player.h"
#include "graphics/Sprite.h"
#include "Result.h"
#include "Effect.h"
#include "M4A1.h"
#include "MP5.h"
#include "Benelli_M4.h"
#include "M110.h"
#include "graphics/Font.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
class HUD;
class Flag;
class Timer;
class GrenadeManager;
class BulletManager;
//�Q�[�����[�h
enum EnGameType {
		enGame_DM,
		enGame_CTF
	};
//�v���C���[�ԍ�
enum EnPlayers {
	enPlayer1,
	enPlayer2,
	enPlayer3,
	enPlayer4,
	enPlayerNum
};
//�Q�[���N���X�B
class Game : public IScene
{
public:
	/// <summary>
	/// �J�����̏��
	/// </summary>
	enum EnCameraType {
		enCamera_TPS,						//TPS
		enCamera_FPS						//FPS
	};
	/// <summary>
	/// �����Ԃ�Ƃ��Ɏg��
	/// </summary>
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
	//�o���b�g�}�l�[�W���[���擾
	BulletManager& GetBulletManager()
	{
		return *m_bulletManager;
	}
	//�O���l�[�h�}�l�[�W���[���擾
	GrenadeManager& GetGrenadeManager()
	{
		return *m_grenadeManager;
	}
	//�}�Y���t���b�V���̃G�t�F�N�g���擾
	Effect &GetMuzzleFlasheEffect(int playerNo)
	{
		return m_muzzleflasheffect[playerNo];
	}
	//�O���l�[�h�̔����̃G�t�F�N�g���擾
	Effect &GetExplosionEffect(int playerNo)
	{
		return m_explosioneffect[playerNo];
	}
	//��ʂɕ\��������̂��擾
	HUD &GetHUD(int playerNo)
	{
		return *m_hud[playerNo];
	}
	//���̃J�����̏�Ԃ��L������
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	/// <summary>
	/// �����Ԃ鎞�Ɏg��
	/// </summary>
	/// <param name="playerNo">�|���ꂽ�v���C���[�ԍ�</param>
	/// <param name="random">0�`3�܂ł̃����_���Ȓl������</param>
	/// <returns>�����Ԃ鎞�Ɏg���\���̂�Ԃ�</returns>
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
	
	//�v���C���[�ɏe����������
	void SetPlayerWeapon()
	{
		for (int i = 0; i < PLAYERS; i++)
		{
			m_player[i]->SetWeapon(enWeapon_M4A1);
		}
	}
private:
	Player *m_player[PLAYERS];											//�v���C���[
	GameCamera* m_gameCamera[PLAYERS];									//�Q�[���J����
	Background* m_background;											//�w�i
	BulletManager* m_bulletManager;										//�e
	EnCameraType m_cameratype = enCamera_FPS;							//�J�����̏��
	bool m_drawflag;													//�v���C���[��`�悷�邩?
	Sky m_sky;															//��B
	Sprite m_copyMainRtToFrameBufferSprite;								//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�̃r���[�|�[�g�B
	Level m_level;														//���x��
	SRespawn m_respawn[enPlayerNum];									//���X�|�[���̎��Ɏg���\����
	float m_restTimer = 180.0f;											//�Q�[���̎c�莞�ԁB�P�ʁF�b�B
	float m_startTimer = 3.0f;											//�Q�[���̊J�n���ԁB�P�ʁF�b�B
	Timer* m_timer;														//�c�莞�Ԃ�`�悷��
	HUD* m_hud[PLAYERS];												//��ʂɕ\���������
	M4A1 m_m4a1[PLAYERS];												//���f��
	MP5 m_mp5[PLAYERS];													//���f��
	M110 m_m110[PLAYERS];												//���f��
	Benelli_M4 m_benelliM4[PLAYERS];		 							//���f��
	Effect m_muzzleflasheffect[PLAYERS];								//�}�Y���t���b�V���̃G�t�F�N�g
	Effect m_explosioneffect[PLAYERS];									//�O���l�[�h�̔����̃G�t�F�N�g
	GrenadeManager* m_grenadeManager;									//�O���l�[�h
	Font m_font;														//�t�H���g
	bool m_weaponflag = true;											//�v���C���[�ɏe����������t���O
	bool m_endflag = false;												//�c�莞�Ԃ�0�ɂȂ������̃t���O
	bool m_transitionflag = false;										//���U���g��ʂɑJ�ڂ��邽�߂̃t���O
	bool m_waitflag = true;												//�Q�[�����n�܂��ď����̊Ԏ~�߂�t���O
	bool m_endSoundflag = true;											//�Q�[���I���̉���炷�t���O
	CSoundSource m_startSound;											//�Q�[���J�n�̓J�̉�
	CSoundSource m_endSound;											//�Q�[���I���̓J�̉�
	Flag* m_flag;														//�L���v�`���[�U�t���b�O�Ŏg���̊�
	int m_gameMode;                                                     //�Z���N�g��ʂőI�����ꂽ�Q�[�����[�h�����Ă������߂̕ϐ�
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;

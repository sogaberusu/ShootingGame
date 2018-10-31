#pragma once

#include "IScene.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"
#include "StoneManager.h"

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

	StoneManager& GetStoneManager()
	{
		return m_stoneManager;
	}
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	void DrowSetFalse()
	{
		m_dorwflag = false;
	}
	void DrowSetTrue()
	{
		m_dorwflag = true;
	}
private:
	Minotaur m_minotaur;				//�v���C���[
	Level m_level;						//���x�����������B
	GameCamera m_gameCamera;
	Background m_bg;
	Goblin m_goblin;
	Orc m_orc;
	StoneManager m_stoneManager;
	EnCameraType m_cameratype = enCamera_FPS;
	bool m_dorwflag = true;
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;

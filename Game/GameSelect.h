#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"

class GameSelect : public IScene
{
public:
	GameSelect();
	~GameSelect();
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;
	
private:
	Sprite m_background;									//�w�i�̉摜
	Sprite m_rightselect;									//�E�����̎O�p�̉摜	
	Sprite m_leftselect;									//�������̎O�p�̉摜
	Sprite m_startButton;									//�X�^�[�g�{�^���̉摜
	Font m_font;											//�t�H���g
	CVector2 m_fontDMPos = { -100.0f,100.0f };				//�t�H���g�u�f�X�}�b�`�v��\��������W
	CVector2 m_fontCTFPos = { 1000.0f,100.0f };				//�t�H���g�u�L���v�`���[�U�t���b�O�v��\��������W
	CVector2 m_fontContainerPos = { -100.0f,-170.0f };		//�t�H���g�u�R���e�i�}�b�v�v��\��������W
	CVector2 m_fontTestMapPos = { 1000.0f,-170.0f };		//�t�H���g�u�e�X�g�}�b�v�v��\��������W
	bool m_leftMoveflag = false;							//���Ɉړ�����������t���O
	bool m_rightMoveflag = false;							//�E�Ɉړ�����������t���O
	enum EnGameType {
		enGame_DM,											//�f�X�}�b�`
		enGame_CTF											//�L���v�`���[�U�t���b�O
	};
	EnGameType m_gametype = enGame_DM;						//�v���C����Q�[�����[�h
	enum EnMapType {
		enMap_Container,									//�R���e�i�}�b�v
		enMap_Test											//�e�X�g�}�b�v
	};
	EnMapType m_maptype = enMap_Container;					//�v���C����}�b�v
	CVector4 Black = { 0.0f,0.0f,0.0f,1.0f };				//��
	CVector4 Red = { 256.0f,0.0f,0.0f,1.0f };				//��
	CVector4 m_gameTypeFontColor = Black;					//�Q�[�����[���̃t�H���g�̐F
	CVector4 m_stageFontColor = Black;						//�X�e�[�W�̃t�H���g�̐F
	CVector4 m_gameStartFontColor = Black;					//�X�^�[�g�̃t�H���g�̐F
	enum EnState {
		enState_GameType,									//�Q�[�����[��
		enState_GameMap,									//�}�b�v�I��
		enState_GameStart,									//�Q�[���J�n
	};
	EnState m_state = enState_GameType;						//���݂̃J�[�\���̈ʒu
};
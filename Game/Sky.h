#pragma once
#include "graphics/Shader.h"
class Sky
{
public:
	Sky();
	~Sky();
	//�`��
	void Draw(Camera& camera);
private:
	SkinModel m_skinModel;										//���f���`��̃Q�[���I�u�W�F�N�g�B
	Shader m_psSkyShader;										//��p�̃V�F�[�_�[�B
};


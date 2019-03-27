#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"

class Title : public IScene
{
public:
	Title();
	~Title();
	//�I�[�o�[���C�h�����֐��ɂ�override�C���q�����Ă���ƍK���ɂȂ��B
	void Update() override;
	//�I�[�o�[���C�h�����֐��ɂ�override�C���q�����Ă���ƍK���ɂȂ��B
	//why?
	//���̊֐��̂悤�Ƀ^�C�v�~�X�������Ƃ��ɃR���p�C���G���[�ɂȂ��ċ����Ă����B
	//void Drow() override;
	void Draw() override;
private:
	Sprite m_sprite;
	CVector3	m_position;		//���W�B
	CQuaternion m_rotation;	//��]�B
	ID3D11ShaderResourceView* m_mikyan = nullptr;
};


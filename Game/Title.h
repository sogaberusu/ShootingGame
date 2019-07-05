#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"

class Title : public IScene
{
public:
	Title();
	~Title();
	void Update() override;
	void Draw() override;
private:
	Sprite m_sprite;
	ID3D11ShaderResourceView* m_background = nullptr;
	Font m_font;
	SkinModel m_model;
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[1];					//アニメーションクリップ。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
};


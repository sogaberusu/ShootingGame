#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"

class Title : public IScene
{
public:
	Title();
	~Title();
	void Update() override;
	void Draw() override;
private:
	Sprite m_sprite;
	ID3D11ShaderResourceView* m_title = nullptr;
};


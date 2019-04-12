#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"

class Title : public IScene
{
public:
	Title();
	~Title();
	//オーバーライドした関数にはoverride修飾子をつけていると幸せになれる。
	void Update() override;
	//オーバーライドした関数にはoverride修飾子をつけていると幸せになれる。
	//why?
	//下の関数のようにタイプミスをしたときにコンパイルエラーになって教えてくれる。
	//void Drow() override;
	void Draw() override;
private:
	Sprite m_sprite;
	ID3D11ShaderResourceView* m_title = nullptr;
	Font m_font;
};


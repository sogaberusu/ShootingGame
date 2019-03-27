#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"

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
	CVector3	m_position;		//座標。
	CQuaternion m_rotation;	//回転。
	ID3D11ShaderResourceView* m_mikyan = nullptr;
};


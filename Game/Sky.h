#pragma once
#include "graphics/Shader.h"
class Sky
{
public:
	Sky();
	~Sky();
	//描画
	void Draw(Camera& camera);
private:
	SkinModel m_skinModel;										//モデル描画のゲームオブジェクト。
	Shader m_psSkyShader;										//空用のシェーダー。
};


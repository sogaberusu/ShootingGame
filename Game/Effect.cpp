#include "stdafx.h"
#include "Effect.h"


Effect::Effect()
{

}


Effect::~Effect()
{
	Release();
}

void Effect::Init(const wchar_t* filepath)
{

	//レンダラーを初期化。
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
		20000										//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());

	//サンプルのエフェクトをロードする。
	m_sampleEffect = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)filepath);

}

void Effect::Play(CVector3 position,CQuaternion rotation, CVector3 scale)
{
	//再生中のエフェクトを止める。
	m_effekseerManager->StopEffect(m_playEffectHandle);

	//再生。
	m_playEffectHandle = m_effekseerManager->Play(m_sampleEffect, 0.0, 0.0, 0.0);

	//エフェクトのベース行列を設定
	CMatrix mTrans, mRot, mScale, mBase;
	mTrans.MakeTranslation(position);
	mRot.MakeRotationFromQuaternion(rotation);
	mScale.MakeScaling(scale);
	mBase.Mul(mScale, mRot);
	mBase.Mul(mBase, mTrans);
	m_effekseerManager->SetBaseMatrix(m_playEffectHandle, mBase);
}

void Effect::Draw(int playerNo)
{
	//Effekseerカメラ行列を設定。
	//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
	Effekseer::Matrix44 efCameraMat;
	g_camera3D[playerNo].GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D[playerNo].GetProjectionMatrix().CopyTo(efProjMat);
	//カメラ行列とプロジェクション行列を設定。
	m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	m_effekseerRenderer->SetProjectionMatrix(efProjMat);
	//Effekseerを更新。
	m_effekseerManager->Update();
	//エフェクトは不透明オブジェクトを描画した後で描画する。
	m_effekseerRenderer->BeginRendering();
	m_effekseerManager->Draw();
	m_effekseerRenderer->EndRendering();

}

void Effect::Release()
{
	if (m_effekseerManager != nullptr) {
		m_effekseerManager->Destroy();
	}

	if (m_effekseerRenderer != nullptr) {
		m_effekseerRenderer->Destroy();
	}

	//エフェクトを破棄。
	if (m_sampleEffect != nullptr) {
		m_sampleEffect->Release();
	}
}
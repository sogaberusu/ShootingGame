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

	//�����_���[���������B
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());

	//�T���v���̃G�t�F�N�g�����[�h����B
	m_sampleEffect = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)filepath);

}

void Effect::Play(CVector3 position,CQuaternion rotation, CVector3 scale)
{
	//�Đ����̃G�t�F�N�g���~�߂�B
	m_effekseerManager->StopEffect(m_playEffectHandle);

	//�Đ��B
	m_playEffectHandle = m_effekseerManager->Play(m_sampleEffect, 0.0, 0.0, 0.0);

	//�G�t�F�N�g�̃x�[�X�s���ݒ�
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
	//Effekseer�J�����s���ݒ�B
	//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
	Effekseer::Matrix44 efCameraMat;
	g_camera3D[playerNo].GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D[playerNo].GetProjectionMatrix().CopyTo(efProjMat);
	//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
	m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	m_effekseerRenderer->SetProjectionMatrix(efProjMat);
	//Effekseer���X�V�B
	m_effekseerManager->Update();
	//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
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

	//�G�t�F�N�g��j���B
	if (m_sampleEffect != nullptr) {
		m_sampleEffect->Release();
	}
}
#pragma once

#include "graphics/Shader.h"
#include "ShadowMap.h"
#include <array>
/*!
*@brief	���f���G�t�F�N�g�B
*/
class ModelEffect : public DirectX::IEffect {
protected:
	std::wstring m_materialName;	//!<�}�e���A�����B
	Shader* m_pVSShader = nullptr;
	Shader* m_pPSShader = nullptr;
	Shader m_vsShader;
	Shader m_psShader;
	Shader m_psSkyShader;
	Shader m_vsShadowMap;			//�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
	Shader m_psShadowMap;		//�V���h�E�}�b�v�����p�̃s�N�Z���V�F�[�_�[�B
	bool isSkining;
	ID3D11ShaderResourceView* m_albedoTex = nullptr;
	ID3D11ShaderResourceView* m_skyTex = nullptr;
	ID3D11ShaderResourceView* m_shadowTex = nullptr;
	int m_renderMode = 0;
	std::array<ID3D11ShaderResourceView*,4> m_albedoTextureStack = { nullptr };
	int m_albedoTextureStackPos = 0;
public:
	ModelEffect()
	{
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		m_psSkyShader.Load("Assets/shader/model.fx", "PSMain_SkyCube", Shader::EnType::PS);
		//�V���h�E�}�b�v�p�̃V�F�[�_�[�����[�h�B
		m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);

		InitSkyTexture();
	}
	virtual ~ModelEffect()
	{
		if (m_albedoTex) {
			m_albedoTex->Release();
		}
	}
	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;

	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}
	void SetAlbedoTexture(ID3D11ShaderResourceView* tex)
	{
		m_albedoTex = tex;
	}
	void SetMatrialName(const wchar_t* matName)
	{
		m_materialName = matName;
	}
	
	bool EqualMaterialName(const wchar_t* name) const
	{
		return wcscmp(name, m_materialName.c_str()) == 0;
	}
	void SetRenderMode(int renderMode)
	{
		m_renderMode = renderMode;
	}
	void InitSkyTexture()
	{
		HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/skyCubeMap.dds", 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &m_skyTex);
	}

	/// <summary>
	/// ���݂̃A���x�h�e�N�X�`�����X�^�b�N�ɑޔ�������B
	/// </summary>
	void PushAlbedoTexture()
	{
		m_albedoTextureStack[m_albedoTextureStackPos] = m_albedoTex;
		m_albedoTex = nullptr;
		m_albedoTextureStackPos++;
	}
	/// <summary>
	/// �X�^�b�N����A���x�h�e�N�X�`�����|�b�v����B
	/// </summary>
	void PopAlbedoTexture()
	{
		m_albedoTextureStackPos--;
		SetAlbedoTexture(m_albedoTextureStack[m_albedoTextureStackPos]);
	}
};
/*!
*@brief
*  �X�L���Ȃ����f���G�t�F�N�g�B
*/
class NonSkinModelEffect : public ModelEffect {
public:
	NonSkinModelEffect()
	{
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		isSkining = false;
	}
};
/*!
*@brief
*  �X�L�����f���G�t�F�N�g�B
*/
class SkinModelEffect : public ModelEffect {
public:
	SkinModelEffect()
	{
		wchar_t hoge[256];
		GetCurrentDirectoryW(256, hoge);
		m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", Shader::EnType::VS);
		m_vsShadowMap.Load("Assets/shader/model.fx", "VSMainSkin_ShadowMap", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		isSkining = true;
	}
};

/*!
*@brief
*  �G�t�F�N�g�t�@�N�g���B
*/
class SkinModelEffectFactory : public DirectX::EffectFactory {
public:
	SkinModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<ModelEffect> effect;
		if (info.enableSkinning) {
			//�X�L�j���O����B
			effect = std::make_shared<SkinModelEffect>();
		}
		else {
			//�X�L�j���O�Ȃ��B
			effect = std::make_shared<NonSkinModelEffect>();
		}
		effect->SetMatrialName(info.name);
		if (info.diffuseTexture && *info.diffuseTexture)
		{
			ID3D11ShaderResourceView* texSRV;
			DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
			effect->SetAlbedoTexture(texSRV);
		}
		return effect;
	}

	void __cdecl CreateTexture(const wchar_t* name, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textureView) override
	{
		return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
	}
};

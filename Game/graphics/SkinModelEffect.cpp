#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	
	switch (m_renderMode) {
	case 0: {
		//通常描画。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		//deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
		//todo シェーダーリソースビューを一気に設定する。
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTex,							//アルベドテクスチャ。
			g_graphicsEngine->GetShadowMap()->GetShadowMapSRV()			//シャドウマップ。
		};
		deviceContext->PSSetShaderResources(0, 1, srvArray);
	}break;
	case 1:
		//空描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSkyShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(2, 1, &m_skyTex);
		break;
	case 2:
		//シャドウマップ生成用のシェーダーを設定。
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
	/*deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);*/

}
#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	switch (m_renderMode) {
	case 0:
		//’Êí•`‰æB
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
		break;
	case 1:
		//‹ó•`‰æB
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSkyShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(2, 1, &m_skyTex);
		break;
	}
	/*deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);*/

}
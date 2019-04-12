/*!
 * @brief	フォント。
 */
#include "stdafx.h"
#include "Font.h"
#include "Game.h"

Font::Font()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_spriteFont = g_graphicsEngine->GetSpriteFont();
	m_scaleMat.MakeScaling(
		{
			g_graphicsEngine->GetFrameBufferWidth() / static_cast<float>(g_graphicsEngine->Get2DSpaceScreenWidth()),
			g_graphicsEngine->GetFrameBufferHeight() / static_cast<float>(g_graphicsEngine->Get2DSpaceScreenHeight()),
			1.0f
		}
	);
}
Font::~Font()
{
}
void Font::Begin()
{
	D3D11_BLEND_DESC BLEND_DETE;
	BLEND_DETE.AlphaToCoverageEnable = false;
	BLEND_DETE.IndependentBlendEnable = false;
	BLEND_DETE.RenderTarget[0].BlendEnable = 1;
	BLEND_DETE.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BLEND_DETE.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BLEND_DETE.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	ID3D11BlendState* BlendState;
	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ID3D11Device* d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&BLEND_DETE, &BlendState);
	d3dDeviceContext->OMSetBlendState(BlendState, nullptr, 0xFFFFFFFF);

	m_spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		BlendState,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_scaleMat
	);
}
void Font::End()
{
	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ID3D11Device* d3dDevice = g_graphicsEngine->GetD3DDevice();

	m_spriteBatch->End();

	////レンダリングステートを戻す。
	{
		//ブレンド設定
		D3D11_BLEND_DESC BLEND_DETE;
		BLEND_DETE.AlphaToCoverageEnable = false;
		BLEND_DETE.IndependentBlendEnable = false;
		BLEND_DETE.RenderTarget[0].BlendEnable = true;
		BLEND_DETE.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		ID3D11BlendState* BlendState;
		d3dDevice->CreateBlendState(&BLEND_DETE, &BlendState);
		d3dDeviceContext->OMSetBlendState(BlendState, nullptr, 0xFFFFFFFF);

		MemoryBarrier();
	}
	d3dDeviceContext->RSSetState(g_graphicsEngine->GetRasterizerState());

	{
		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable = true;
		desc.DepthWriteMask = false ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		desc.StencilEnable = false;
		desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

		desc.BackFace = desc.FrontFace;

		ID3D11DepthStencilState* depthStencilState;
		d3dDevice->CreateDepthStencilState(&desc, &depthStencilState);
		d3dDeviceContext->OMSetDepthStencilState(depthStencilState, 0);
		MemoryBarrier();

	}
}
void Font::Draw(
	wchar_t const* text,
	const CVector2& position,
	const CVector4& color,
	float rotation,
	float scale,
	CVector2 pivot)
{
	pivot.y = 1.0f - pivot.y;
	DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
	//座標系をスプライトと合わせる。
	CVector2 pos = position;
	float frameBufferHalfWidth = g_graphicsEngine->Get2DSpaceScreenWidth() * 0.5f;
	float frameBufferHalfHeight = g_graphicsEngine->Get2DSpaceScreenHeight() * 0.5f;
	pos.x += frameBufferHalfWidth;
	pos.y = -pos.y + frameBufferHalfHeight;

	if (m_isDrawShadow) {
		//影を書く。
		CVector2 offsetTbl[] = {
			{ m_shadowOffset , 0.0f},
			{ -m_shadowOffset , 0.0f },
			{ 0.0f , m_shadowOffset },
			{ 0.0f , -m_shadowOffset },
			{ m_shadowOffset ,  m_shadowOffset },
			{ m_shadowOffset ,  -m_shadowOffset },
			{ -m_shadowOffset , m_shadowOffset },
			{ -m_shadowOffset , -m_shadowOffset },
		};
		for (auto offset : offsetTbl) {
			CVector2 sPos = pos;
			sPos.x += offset.x;
			sPos.y += offset.y;
			m_spriteFont->DrawString(
				m_spriteBatch,
				text,
				sPos.vec,
				m_shadowColor,
				rotation,
				DirectX::XMFLOAT2(pivot.x, pivot.y),
				scale
			);
		}
	}
	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);
}
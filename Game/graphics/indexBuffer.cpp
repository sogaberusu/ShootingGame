#include "stdafx.h"
#include "indexBuffer.h"


indexBuffer::indexBuffer()
{
}


indexBuffer::~indexBuffer()
{
	Release();
}
void indexBuffer::Release()
{
	if (m_indexBuffer) {
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}
}
bool indexBuffer::Create(int numIndex, EnIndexType indexType, const void* pSrcIndexBuffer)
{
	Release();

	int stride = 0;
	if (indexType == enIndexType_16) {
		//16bit
		stride = 2;
	}
	else {
		//32bit
		stride = 4;
	}
	m_numIndex = numIndex;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = stride * numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pSrcIndexBuffer;

	HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}
#include "stdafx.h"
#include "SpriteData.h"


SpriteData::SpriteData()
{
}


SpriteData::~SpriteData()
{
}
void SpriteData::Release()
{
	m_vertexBuffer.Release();
	m_indexBuffer.Release();
}
bool SpriteData::Create(
	D3D_PRIMITIVE_TOPOLOGY topology,
	int numVertex,
	int vertexStride,
	void* pSrcVertexBuffer,
	int numIndex,
	indexBuffer::EnIndexType indexType,
	void* pSrcIndexBuffer)
{
	Release();
	m_topology = topology;
	bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
	if (!result) {
		throw;
		return false;
	}
	if (pSrcIndexBuffer) {
		result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
		if (!result) {
			throw;
			return false;
		}
	}
	return true;
}
void SpriteData::Draw(ID3D11DeviceContext& rc)
{

	//���_�o�b�t�@��ݒ�B
	UINT ofset = 0;
	UINT stride = m_vertexBuffer.GetStride();
	rc.IASetVertexBuffers(0,1,&(m_vertexBuffer.GetBody()), &stride, &ofset);
	auto type = m_indexBuffer.GetIndexType();
	rc.IASetIndexBuffer(
		m_indexBuffer.GetBody(),
		type == indexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
		0
		);
	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	rc.IASetPrimitiveTopology(m_topology);
	//�`��B
	rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
}

void SpriteData::Draw(ID3D11DeviceContext& rc, int numVertex)
{
	//���_�o�b�t�@��ݒ�B
	UINT ofset = 0;
	UINT stride = m_vertexBuffer.GetStride();
	rc.IASetVertexBuffers(0, 1, &(m_vertexBuffer.GetBody()), &stride, &ofset);
	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	rc.IASetPrimitiveTopology(m_topology);
	//�`��B
	rc.Draw(numVertex, 0);
}
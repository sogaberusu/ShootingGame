#pragma once
#include"indexBuffer.h"
#include"vertexBuffer.h"
class SpriteData
{
public:
	SpriteData();
	~SpriteData();
	/*!
	*@brief	�v���~�e�B�u�쐬�B
	*@param[in]	topology			�g�|���W�[�B
	*@param[in]	numVertex			���_�̐��B
	*@param[in]	vertexStride		���_�X�g���C�h�B
	*@param[in]	pSrcVertexBuffer	�\�[�X�ƂȂ钸�_�o�b�t�@�B
	*@param[in]	numIndex			�C���f�b�N�X�̐��B
	*@param[in]	indexType			�C���f�b�N�X�̌^�B
	*@param[in]	pSrcIndexBuffer		�\�[�X�ƂȂ�C���f�b�N�X�o�b�t�@�B
	*@retval	true	�쐬����
	*@retval	false	�쐬���s�B
	*/
	bool Create(
		D3D_PRIMITIVE_TOPOLOGY topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		indexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer
	);
	/*!
	*@brief	�����I�Ƀ����[�X�B
	*/
	void Release();	
	/*!
	*@brief	���_�o�b�t�@���擾�B
	*/
	vertexBuffer& GetVertexBuffer()
	{
		return m_vertexBuffer;
	}
	/*!
	*@brief	�`��B
	*/
	void Draw(ID3D11DeviceContext& rc);
	/*!
	*@brief	�`��B
	*/
	void Draw(ID3D11DeviceContext& rc, int numVertex);

private:
	vertexBuffer			m_vertexBuffer;		//!<���_�o�b�t�@�B
	indexBuffer		     	m_indexBuffer;		//!<�C���f�b�N�X�o�b�t�@�B
	D3D_PRIMITIVE_TOPOLOGY	m_topology;			//!<�g�|���W�[�B
};


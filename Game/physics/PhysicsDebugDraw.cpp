#include "stdafx.h"
#include "PhysicsDebugDraw.h"


void PhysicsDebugDraw::Init()
{
	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		static_cast<int>(m_vertexBuffer.size()),
		sizeof(CVector4),
		&m_vertexBuffer[0],
		0,
		indexBuffer::enIndexType_32,
		nullptr
	);
	m_vs.Load("Assets/shader/linePrimitive.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/linePrimitive.fx", "PSMain", Shader::EnType::PS);

	//ConstantBuffer用のバッファ定義を作成する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = (((sizeof(SConstantBuffer) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	HRESULT hr;
	if (nullptr) {
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = nullptr;
		hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, &InitData, &m_cb);
	}
	else {
		hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
	}
	//ConstantBuffer用のバッファ定義を作成する。
	D3D11_BUFFER_DESC bufferDesc1;
	ZeroMemory(&bufferDesc1, sizeof(bufferDesc1));
	bufferDesc1.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc1.ByteWidth = (((sizeof(CVector4) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	bufferDesc1.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc1.CPUAccessFlags = 0;

	HRESULT hr1;
	if (nullptr) {
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = nullptr;
		hr1 = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, &InitData, &m_cb2);
	}
	else {
		hr1 = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb2);
	}
}
void PhysicsDebugDraw::BeginDraw()
{
	DeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	m_numLine = 0;
}
void PhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	//物理エンジンからもらった情報を
	int baseIndex = m_numLine * 2;
	m_vertexBuffer[baseIndex].Set(CVector3(from.x(), from.y(), from.z()));
	m_vertexBuffer[baseIndex + 1].Set(CVector3(to.x(), to.y(), to.z()));
	m_numLine++;
}
void PhysicsDebugDraw::EndDraw()
{
	//定数バッファの更新。
	SConstantBuffer cb;
	cb.mView = g_camera3D[3].GetViewMatrix();
	cb.mProj = g_camera3D[3].GetProjectionMatrix();
	CVector4 colr;
	colr = { 0.0f,1.0f,0.0f,1.0f };
	DeviceContext->UpdateSubresource(m_cb2, 0, NULL, &colr, 0, 0);
	DeviceContext->PSSetConstantBuffers(1, 1, &(m_cb2));
	DeviceContext->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	DeviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	DeviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, &(m_cb));
	//入力レイアウトを設定。
	DeviceContext->IASetInputLayout(m_vs.GetInputLayout());
	DeviceContext->UpdateSubresource(m_primitive.GetVertexBuffer().GetBody(), 0, NULL, &m_vertexBuffer[0], 0, 0);
	m_primitive.Draw(*DeviceContext, m_numLine * 2);
}
#include <DX3D/Graphics/VertexBuffer.h>

dx3d::VertexBuffer::VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_vertexSize(desc.vertexSize), m_vertexListSize(desc.vertexListSize)
{
	if (!desc.vertexList) DX3DLogThrowInvalidArg("No vertex list provided."); //檢查頂點緩衝描述子，必須為非空
	if (!desc.vertexListSize) DX3DLogThrowInvalidArg("Vertex list size must be non-zero.");
	if (!desc.vertexSize) DX3DLogThrowInvalidArg("Vertex size must be non-zero");

	D3D11_BUFFER_DESC buffDesc{};  //建置descriptor去定義緩衝大小、使用量、bind flags、cpu,gpu的access
	buffDesc.ByteWidth = desc.vertexListSize * desc.vertexSize;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //綁定旗標: 告訴GPU我要把某塊記憶體當作頂點緩衝使用
	
	D3D11_SUBRESOURCE_DATA initData{}; //D3D11_subresource: 在creation時，初始化cpu side data給GPU resource
	initData.pSysMem = desc.vertexList; //預期一個custom空指針給initial data

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateBuffer(&buffDesc, &initData, &m_buffer), //Get d3d11 device
		"CreateBuffer failed.");
}

dx3d::ui32 dx3d::VertexBuffer::gerVertexListSize() const noexcept
{
	return m_vertexListSize;
}

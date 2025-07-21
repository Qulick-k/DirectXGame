#include <DX3D/Graphics/VertexBuffer.h>

dx3d::VertexBuffer::VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_vertexSize(desc.vertexSize), m_vertexListSize(desc.vertexListSize)
{
	if (!desc.vertexList) DX3DLogThrowInvalidArg("No vertex list provided."); //�ˬd���I�w�Ĵy�z�l�A�������D��
	if (!desc.vertexListSize) DX3DLogThrowInvalidArg("Vertex list size must be non-zero.");
	if (!desc.vertexSize) DX3DLogThrowInvalidArg("Vertex size must be non-zero");

	D3D11_BUFFER_DESC buffDesc{};  //�ظmdescriptor�h�w�q�w�Ĥj�p�B�ϥζq�Bbind flags�Bcpu,gpu��access
	buffDesc.ByteWidth = desc.vertexListSize * desc.vertexSize;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //�j�w�X��: �i�DGPU�ڭn��Y���O�����@���I�w�Ĩϥ�
	
	D3D11_SUBRESOURCE_DATA initData{}; //D3D11_subresource: �bcreation�ɡA��l��cpu side data��GPU resource
	initData.pSysMem = desc.vertexList; //�w���@��custom�ū��w��initial data

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateBuffer(&buffDesc, &initData, &m_buffer), //Get d3d11 device
		"CreateBuffer failed.");
}

dx3d::ui32 dx3d::VertexBuffer::gerVertexListSize() const noexcept
{
	return m_vertexListSize;
}

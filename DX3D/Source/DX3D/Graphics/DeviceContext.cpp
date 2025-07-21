#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc)
{
	DX3DGraphicsLogThrowOnFail(m_device.CreateDeferredContext(0, &m_context),
		"CreateDeferredContext failed");
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	f32 fColor[] = { color.x, color.y, color.z, color.w };
	auto rtv = swapChain.m_rtv.Get();
	m_context->ClearRenderTargetView(rtv, fColor);
	m_context->OMSetRenderTargets(1, &rtv, nullptr);
}

void dx3d::DeviceContext::setGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
	//�j�w�iIA��J�ոˡj��InputLauout�igraphics pipeline�A�i�DGPU�p�����binary structure��vertex���
	m_context->IASetInputLayout(pipeline.m_layout.Get());    //�H�Φp��map�nvertex shader���w����J
	m_context->VSSetShader(pipeline.m_vs.Get(), nullptr, 0); //�j�wvertex shader�iGPU pipeline
	m_context->PSSetShader(pipeline.m_ps.Get(), nullptr, 0);
}

void dx3d::DeviceContext::setVertexBuffer(const VertexBuffer& buffer)
{
	auto stride = buffer.m_vertexSize;         //�qVB class���^vertex�j�p
	auto buf = buffer.m_buffer.Get();          //���^buffer����
	auto offset = 0u;                          //�ϥ�u��ܨϥ�unsigned interger value
	m_context->IASetVertexBuffers(0, 1, &buf, &stride, &offset);
}

void dx3d::DeviceContext::setViewportSize(const Rect& size)
{
	D3D11_VIEWPORT vp{};         //�w�qD3D11_VIEWPORT���O�����a�ܼ�
	vp.Width = static_cast<f32>(size.width); //�ѩ�D3D11_VIEWPORT�A��float�A�]���ϥ�static_cast�ഫ���
	vp.Height = static_cast<f32>(size.height);
	vp.MinDepth = 0.0f;    //��ܱq���Y�̪�]0�^��̻��]1�^���骺��ܽd��C
	vp.MaxDepth = 1.0f;
	m_context->RSSetViewports(1, &vp);  //�]�w�X��ϧη|�b���̳Q���]�Ʀb�ù��W
}

void dx3d::DeviceContext::drawTriangleList(ui32 vertexCount, ui32 startVertexLocation)
{
	//�w�q��J�ո˶��q�p��interpret(����)vertex data
	//�ר�O�ո�data into geometric primitives(�X�����,AKA.�T���ΡB���u�B�I)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//Ĳ�oø�ϫ��O�A�Ѽƥ]�Avertex count�M�_�lvertex��m
	m_context->Draw(vertexCount, startVertexLocation);
}

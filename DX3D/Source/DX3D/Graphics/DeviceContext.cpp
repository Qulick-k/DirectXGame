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
	//綁定【IA輸入組裝】至InputLauout進graphics pipeline，告訴GPU如何解釋binary structure的vertex資料
	m_context->IASetInputLayout(pipeline.m_layout.Get());    //以及如何map好vertex shader的預期輸入
	m_context->VSSetShader(pipeline.m_vs.Get(), nullptr, 0); //綁定vertex shader進GPU pipeline
	m_context->PSSetShader(pipeline.m_ps.Get(), nullptr, 0);
}

void dx3d::DeviceContext::setVertexBuffer(const VertexBuffer& buffer)
{
	auto stride = buffer.m_vertexSize;         //從VB class取回vertex大小
	auto buf = buffer.m_buffer.Get();          //取回buffer指標
	auto offset = 0u;                          //使用u表示使用unsigned interger value
	m_context->IASetVertexBuffers(0, 1, &buf, &stride, &offset);
}

void dx3d::DeviceContext::setViewportSize(const Rect& size)
{
	D3D11_VIEWPORT vp{};         //定義D3D11_VIEWPORT型別的本地變數
	vp.Width = static_cast<f32>(size.width); //由於D3D11_VIEWPORT適用float，因此使用static_cast轉換單位
	vp.Height = static_cast<f32>(size.height);
	vp.MinDepth = 0.0f;    //表示從鏡頭最近（0）到最遠（1）物體的顯示範圍。
	vp.MaxDepth = 1.0f;
	m_context->RSSetViewports(1, &vp);  //設定幾何圖形會在哪裡被光柵化在螢幕上
}

void dx3d::DeviceContext::drawTriangleList(ui32 vertexCount, ui32 startVertexLocation)
{
	//定義輸入組裝階段如何interpret(解釋)vertex data
	//尤其是組裝data into geometric primitives(幾何基本體,AKA.三角形、直線、點)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//觸發繪圖指令，參數包括vertex count和起始vertex位置
	m_context->Draw(vertexCount, startVertexLocation);
}

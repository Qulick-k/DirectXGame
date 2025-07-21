#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Math/Vec3.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	//使用constexpr 在compile time evaluate數值
	constexpr char shaderSourceCode[] =               //vertex shader code
//把模型的頂點位置傳進來，加上一個 w=1.0，然後傳回，讓 GPU 知道這個頂點要畫在哪裡
//POSITION為語意標記（Semantic），代表輸入的頂點位置。
		R"(
float4 VSMain(float3 pos: POSITION): SV_Position     
{
return float4(pos.xyz, 1.0);                      
}
float4 PSMain(): SV_Target
{
return float4(1.0, 1.0, 1.0, 1.0);  //這個pixel shader會回傳白色
}
)";
	constexpr char shaderSourceName[] = "Basic";
	constexpr auto shaderSourceCodeSize = std::size(shaderSourceCode);

	auto vs = device.compileShader({shaderSourceName, shaderSourceCode, shaderSourceCodeSize,
		"VSMain", ShaderType::VertexShader});
	auto ps = device.compileShader({ shaderSourceName, shaderSourceCode, shaderSourceCodeSize,
		"PSMain", ShaderType::PixelShader });

	m_pipeline = device.createGraphicsPipelineState({ *vs, *ps });

	const Vec3 vertexList[] =       //填上三角形的3個vertex座標
	{
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	m_vb = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vec3)}); //sizeof 取得Vec3占用多少記憶體
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 1,0,0,1});
	context.setGraphicsPipelineState(*m_pipeline);
	
	context.setViewportSize(swapChain.getSize()); //設定viewboard size，傳送當前swap chain的大小

	auto& vb = *m_vb;                  //取回vertex buffer的參考
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.gerVertexListSize(), 0u);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}

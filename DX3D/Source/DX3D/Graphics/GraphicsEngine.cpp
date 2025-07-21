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

	//�ϥ�constexpr �bcompile time evaluate�ƭ�
	constexpr char shaderSourceCode[] =               //vertex shader code
//��ҫ������I��m�Ƕi�ӡA�[�W�@�� w=1.0�A�M��Ǧ^�A�� GPU ���D�o�ӳ��I�n�e�b����
//POSITION���y�N�аO�]Semantic�^�A�N���J�����I��m�C
		R"(
float4 VSMain(float3 pos: POSITION): SV_Position     
{
return float4(pos.xyz, 1.0);                      
}
float4 PSMain(): SV_Target
{
return float4(1.0, 1.0, 1.0, 1.0);  //�o��pixel shader�|�^�ǥզ�
}
)";
	constexpr char shaderSourceName[] = "Basic";
	constexpr auto shaderSourceCodeSize = std::size(shaderSourceCode);

	auto vs = device.compileShader({shaderSourceName, shaderSourceCode, shaderSourceCodeSize,
		"VSMain", ShaderType::VertexShader});
	auto ps = device.compileShader({ shaderSourceName, shaderSourceCode, shaderSourceCodeSize,
		"PSMain", ShaderType::PixelShader });

	m_pipeline = device.createGraphicsPipelineState({ *vs, *ps });

	const Vec3 vertexList[] =       //��W�T���Ϊ�3��vertex�y��
	{
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	m_vb = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vec3)}); //sizeof ���oVec3�e�Φh�ְO����
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
	
	context.setViewportSize(swapChain.getSize()); //�]�wviewboard size�A�ǰe��eswap chain���j�p

	auto& vb = *m_vb;                  //���^vertex buffer���Ѧ�
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.gerVertexListSize(), 0u);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}

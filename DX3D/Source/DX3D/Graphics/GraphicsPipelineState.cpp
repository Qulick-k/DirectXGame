#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc,
	const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc)
{
	if (desc.vs.getType() != ShaderType::VertexShader) //check if the type returned doesn't correspond
		DX3DLogThrowInvalidArg("The 'vs' member is not a valid vertx shader binary.");
	if (desc.ps.getType() != ShaderType::PixelShader)
		DX3DLogThrowInvalidArg("The 'ps' member is not a valid pixel shader binary.");

	auto vs = desc.vs.getData();          //retrive vertex shader data
	auto ps = desc.ps.getData();          //retrive pixel shader data
	
	constexpr D3D11_INPUT_ELEMENT_DESC elements[] = //一個指標指向d3d11輸入元素desk物件，描述節點格式如位置或顏色
	{
		//第二個屬性用來區分不同的變數，但是共用同一個Semantic的名字
		//第四個屬性告訴d3d vertex buffer的元素從哪來
		//第六個屬性被用來Instance rendering，目前專案沒使用，因此設為0
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
		
	DX3DGraphicsLogThrowOnFail(
		m_device.CreateInputLayout(elements, std::size(elements), vs.data, vs.dataSize, &m_layout),
		"CreateInputLayout failed.");   //透過呼叫輸入布局，創建布局

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateVertexShader(vs.data, vs.dataSize, nullptr, &m_vs),
		"CreateVertexShader failed.");   //check the result on fail macro

	DX3DGraphicsLogThrowOnFail(
		m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader failed.");
}
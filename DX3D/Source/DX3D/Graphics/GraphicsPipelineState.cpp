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
	
	DX3DGraphicsLogThrowOnFail(
		m_device.CreateVertexShader(vs.data, vs.dataSize, nullptr, &m_vs),
		"CreateVertexShader failed.");   //check the result on fail macro

	DX3DGraphicsLogThrowOnFail(
		m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader failed.");
}
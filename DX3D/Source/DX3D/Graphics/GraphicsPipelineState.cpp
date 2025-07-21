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
	
	constexpr D3D11_INPUT_ELEMENT_DESC elements[] = //�@�ӫ��Ы��Vd3d11��J����desk����A�y�z�`�I�榡�p��m���C��
	{
		//�ĤG���ݩʥΨӰϤ����P���ܼơA���O�@�ΦP�@��Semantic���W�r
		//�ĥ|���ݩʧi�Dd3d vertex buffer�������q����
		//�Ĥ����ݩʳQ�Ψ�Instance rendering�A�ثe�M�רS�ϥΡA�]���]��0
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
		
	DX3DGraphicsLogThrowOnFail(
		m_device.CreateInputLayout(elements, std::size(elements), vs.data, vs.dataSize, &m_layout),
		"CreateInputLayout failed.");   //�z�L�I�s��J�����A�Ыإ���

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateVertexShader(vs.data, vs.dataSize, nullptr, &m_vs),
		"CreateVertexShader failed.");   //check the result on fail macro

	DX3DGraphicsLogThrowOnFail(
		m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader failed.");
}
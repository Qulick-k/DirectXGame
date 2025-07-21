#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
	class GraphicsPipelineState final : public GraphicsResource
	{
	public:
		GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc);
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs{};     //ComPtr是智慧指標，避免記憶體洩漏
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps{};      //當ComPtr被銷毀時，它會自動呼叫 Release()
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout{};
		friend class DeviceContext;
	};
}



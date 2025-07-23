#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
	class VertexBuffer final: public GraphicsResource
	{
	public:
		VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gDesc);
		ui32 gerVertexListSize() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};  //保管最終緩衝物件
		ui32 m_vertexSize{};
		ui32 m_vertexListSize{};

		friend class DeviceContext; 
	};
}



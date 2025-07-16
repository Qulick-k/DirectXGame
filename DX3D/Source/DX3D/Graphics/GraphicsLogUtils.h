#pragma once
#include <DX3D/Core/Logger.h>
#include <d3d11.h>

namespace dx3d
{
	namespace GraphicsLogUtils
	{
		inline void CheckShaderCompile(Logger& logger, HRESULT hr, ID3DBlob* errorBlob)
		{
			//有否錯誤訊息
			auto errorMsg = errorBlob ? static_cast<const char*>(errorBlob->GetBufferPointer()) : nullptr;

			if (FAILED(hr))
			{
				if (errorMsg)
				{
					DX3DLogThrow(logger, std::runtime_error, Logger::LogLevel::Error, errorMsg);
				}
				else
				{
					DX3DLogThrow(logger, std::runtime_error, Logger::LogLevel::Error, 
						"Shader compilation failed.");
				}
			}

			if (errorMsg)
			{
				//如果有錯誤訊息，則記錄
				DX3DLog(logger, Logger::LogLevel::Warning, errorMsg);
			}
		}
	}
}

#define DX3DGraphicsLogThrowOnFail(hr, message)\
	{\
	auto res = (hr);\
	if (FAILED(res))\
		DX3DLogThrowError(message);\
	}

#define DX3DGraphicsCheckShaderCompile(hr, errorBlob)\
{\
auto res = (hr);\
dx3d::GraphicsLogUtils::CheckShaderCompile(getLogger(), res, errorBlob);\
}
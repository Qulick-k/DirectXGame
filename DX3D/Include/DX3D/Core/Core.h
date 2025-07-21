#pragma once
#include <stdexcept>
#include <memory>

namespace dx3d
{
	class Base;
	class Window;
	class Game;
	class GraphicsEngine;
	class GraphicsDevice;
	class Logger;
	class SwapChain;
	class Display;
	class DeviceContext;
	class ShaderBinary;
	class GraphicsPipelineState;
	class VertexBuffer;

	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;


	using SwapChainPtr = std::shared_ptr<SwapChain>;
	using DeviceContextPtr = std::shared_ptr<DeviceContext>;
	using ShaderBinaryPtr = std::shared_ptr<ShaderBinary>;
	using GraphicsPipelineStatePtr = std::shared_ptr<GraphicsPipelineState>;

	//�� std::shared_ptr<VertexBuffer> �o�ӫ��O�A���F�@��²�u�n�O���O�W VertexBufferPtr�C
	using VertexBufferPtr = std::shared_ptr<VertexBuffer>; //���O�O�W�ŧi�]type alias declaration�^
}
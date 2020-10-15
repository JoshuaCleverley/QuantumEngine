#include <qupch.h>
#include <Quantum/Renderer/Buffer.h>
#include <Quantum/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Quantum {

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		QU_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		QU_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		QU_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		QU_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}

}
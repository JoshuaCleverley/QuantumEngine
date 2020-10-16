#include <qupch.h>

#include <Quantum/Renderer/VertexArray.h>
#include <Quantum/Renderer/Renderer.h>

#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Quantum {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		QU_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
			case RendererAPI::API::OpenGL:	    return new OpenGLVertexArray();
		}

		QU_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
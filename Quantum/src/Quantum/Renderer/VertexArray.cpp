#include <qupch.h>

#include <Quantum/Renderer/VertexArray.h>
#include <Quantum/Renderer/Renderer.h>

#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Quantum {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		QU_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		QU_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
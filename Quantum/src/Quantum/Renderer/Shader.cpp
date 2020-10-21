#include <qupch.h>

#include <Quantum/Renderer/Shader.h>
#include <Quantum/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace Quantum {

	Shader* Shader::CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		QU_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::API::OpenGL:	    return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		QU_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
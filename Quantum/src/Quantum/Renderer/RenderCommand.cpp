#include <qupch.h>

#include <Quantum/Renderer/RenderCommand.h>
#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace Quantum {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}

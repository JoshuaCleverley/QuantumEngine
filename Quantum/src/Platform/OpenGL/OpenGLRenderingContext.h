#pragma once

#include <Quantum/Renderer/RenderingContext.h>

struct GLFWwindow;

namespace Quantum {

	class OpenGLRenderingContext : public RenderingContext
	{
	public:
		OpenGLRenderingContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

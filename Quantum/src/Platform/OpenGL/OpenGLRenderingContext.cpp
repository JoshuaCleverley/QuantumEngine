#include "qupch.h"
#include <Platform/OpenGL/OpenGLRenderingContext.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace Quantum {
	OpenGLRenderingContext::OpenGLRenderingContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		QU_CORE_ASSERT(windowHandle, "windowHandle is null!");
	}

	void OpenGLRenderingContext::Init() 
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QU_CORE_ASSERT(status, "Failed to initialise Glad!");

		QU_CORE_INFO("OpenGL Graphics Info:");
		QU_CORE_INFO("     Vendor: {0}", glGetString(GL_VENDOR));
		QU_CORE_INFO("     Renderer: {0}", glGetString(GL_RENDERER));
		QU_CORE_INFO("     Version: {0}", glGetString(GL_VERSION));

	}
	void OpenGLRenderingContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
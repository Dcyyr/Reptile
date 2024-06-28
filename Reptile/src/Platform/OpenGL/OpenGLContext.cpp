#include "rppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Reptile {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		RP_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		RP_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RP_CORE_ASSERT(status, "Failed to initialize Glad!");

		RP_CORE_INFO("OpenGL Info:");
		

	}

	void OpenGLContext::SwapBuffers()
	{
		RP_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}
#include"rppch.h"
#include"OpenGLContext.h"

#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<gl/GL.h>
namespace Reptile {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		RP_CORE_ASSERT(windowHandle, "window handle is null!"); //´°¿Ú¾ä±úÎª¿Õ
	}

	void OpenGLContext::Init()
	{
		
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RP_CORE_ASSERT(status, "³õÊ¼»¯gladÊ§°Ü");
		
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
#include"rppch.h"
#include"OpenGLContext.h"

#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<gl/GL.h>
namespace Reptile {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		RP_CORE_ASSERT(windowHandle, "window handle is null!"); //���ھ��Ϊ��
	}

	void OpenGLContext::Init()
	{
		
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RP_CORE_ASSERT(status, "��ʼ��gladʧ��");
		
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
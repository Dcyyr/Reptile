#pragma once

#include"Reptile/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Reptile {

	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init();
		virtual void SwapBuffer();

	private:
		GLFWwindow* m_WindowHandle;

	};
}
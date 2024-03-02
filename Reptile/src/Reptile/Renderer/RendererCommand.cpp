#include"rppch.h"
#include"Reptile/Renderer/RendererCommand.h"

#include"Platform/OpenGL/OpenGLRendererAPI.h"

namespace Reptile {

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}
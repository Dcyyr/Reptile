#include"rppch.h"
#include"Reptile/Renderer/RendererCommand.h"

#include"Platform/OpenGL/OpenGLRendererAPI.h"

namespace Reptile {

	Scope<RendererAPI> RendererCommand::s_RendererAPI = RendererAPI::Create();
}
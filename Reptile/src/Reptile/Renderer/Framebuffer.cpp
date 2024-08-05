#include "rppch.h"
#include "Framebuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Reptile {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: RP_CORE_ASSERT(false, "UNKNOW API"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFramebuffer>(spec);
		}

		RP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

#pragma once

#include"Reptile/Renderer/RendererAPI.h"

namespace Reptile {

	class OpenGLRendererAPI :public RendererAPI
	{
	public:
		virtual void Init()override;

		virtual void SetClearColor(const glm::vec4& color)override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Reptile::Ref<VertexArray>& vertexArray)override;
	};
}
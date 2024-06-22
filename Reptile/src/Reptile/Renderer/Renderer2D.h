#pragma once

#include "OrthographicsCamera.h"
#include "Texture.h"

namespace Reptile {

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthographicsCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture);

	};

}
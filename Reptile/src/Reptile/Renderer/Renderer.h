#pragma once

#include"RendererCommand.h"

#include"OrthographicsCamera.h"
#include"Shader.h"

namespace Reptile {


	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicsCamera& camera);
		static void EndScene();

		static void Submit(const Reptile::Ref<Shader>& shader,const Reptile::Ref<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
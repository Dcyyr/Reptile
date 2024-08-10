#pragma once

#include"Reptile.h"

namespace Reptile {

	class EditorLayer :public Reptile::Layer
	{
	public:
		EditorLayer();
		~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts)override;
		void OnEvent(Event& e)override;
		virtual void OnImGuiRender()override;
	private:
		OrthographicCameraController m_CameraController;

		Ref<VertexArray>m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Texture2D> m_CheckboardTexture;
		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportSize = { 0.0f,0.0f };
		glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };

	};
}
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
<<<<<<< HEAD
		
		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

<<<<<<< HEAD
=======
		Entity m_SquareEntity;
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
=======
		Ref<Scene> m_ActiveScene;

		Entity m_SquareEntity;
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f,0.0f };
		glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };

	};
}
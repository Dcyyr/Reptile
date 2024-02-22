#pragma once

#include"Core.h"

#include"Reptile/Events/Event.h"
#include"Reptile/Events/ApplicationEvent.h"
#include"Reptile/LayerStack.h"
#include"Reptile/ImGui/ImGuiLayer.h"
#include"Window.h"

#include"Reptile/Renderer/Shader.h"
#include"Reptile/Renderer/Buffer.h"

namespace Reptile {

		class REPTILE_API Application
		{
		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event& e);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);

		
			inline Window& GetWindow() { return *m_Window; }
			inline static Application& Get() { return *s_Instance; }
		private:
			bool OnWindowClose(WindowCloseEvent& e);
			ImGuiLayer* m_ImGuiLayer;
			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			LayerStack m_LayerStack;

			unsigned int m_VertexArray;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<VertexBuffer> m_VertexBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
		private:
			static Application* s_Instance;

			
		};


		Application* CreateApplication();

}
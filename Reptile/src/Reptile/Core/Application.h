#pragma once

#include "Core.h"

#include "Window.h"
#include "Reptile/Core/LayerStack.h"
#include "Reptile/Events/Event.h"
#include "Reptile/Events/ApplicationEvent.h"

#include "Reptile/Core/Timestep.h"

#include "Reptile/ImGui/ImGuiLayer.h"

namespace Reptile {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
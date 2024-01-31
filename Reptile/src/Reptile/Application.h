#pragma once

#include"Core.h"

#include"Reptile/Events/Event.h"
#include"Reptile/Events/ApplicationEvent.h"
#include"Reptile/LayerStack.h"
#include"Window.h"

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

			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			LayerStack m_LayerStack;

		private:
			static Application* s_Instance;
		};


		Application* CreateApplication();

}
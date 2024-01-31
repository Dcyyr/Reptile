#pragma once

#include"rppch.h"

#include"Reptile/Core.h"
#include"Reptile/Events/Event.h"

namespace Reptile {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Reptile Engine",
						unsigned int width = 1600,
						unsigned int height = 900)
			:Title(title),Width(width),Height(height){}
	};

	class REPTILE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;//Fn=Function

		virtual ~Window(){}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Ù–‘
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Window* Create(const WindowProps& Props = WindowProps());


	};
}
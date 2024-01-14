#include"rppch.h"

#include "Application.h"
#include"Reptile/Events/ApplicationEvent.h"
#include"Reptile/Log.h"

namespace Reptile{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			RP_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			RP_TRACE(e);
		}
		while (true);
	}

}
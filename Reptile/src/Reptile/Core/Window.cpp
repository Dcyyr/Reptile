#include "rppch.h"
#include "Window.h"

#ifdef RP_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Reptile {

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef RP_PLATFORM_WINDOWS
				return std::make_unique<WindowsWindow>(props);
		#else 
				RP_CORE_ASSERT(false, "Unknow Platform");
				return nullptr;
		#endif
	}

}
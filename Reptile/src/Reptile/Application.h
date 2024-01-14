#pragma once

#include"Core.h"
#include"Events/Event.h"

namespace Reptile {

class REPTILE_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();
};

Application* CreateApplication();

}


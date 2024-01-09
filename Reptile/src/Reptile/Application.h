#pragma once

#include"Core.h"

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


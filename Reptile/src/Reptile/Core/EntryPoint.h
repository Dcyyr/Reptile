#pragma once

#ifdef RP_PLATFORM_WINDOWS

extern Reptile::Application* Reptile::CreateApplication();

int main()
{
	Reptile::Log::Init();
	RP_CORE_WARN("Initialized Log!");
	RP_INFO("Hello");
	

	auto app = Reptile::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Reptile only support on windows!
#endif
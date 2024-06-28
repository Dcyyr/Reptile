#pragma once

#ifdef RP_PLATFORM_WINDOWS

extern Reptile::Application* Reptile::CreateApplication();

int main()
{
	Reptile::Log::Init();
	
	RP_PROFILE_BEGIN_SESSION("Startup", "ReptileProfile-Startup-json");
	auto app = Reptile::CreateApplication();
	RP_PROFILE_END_SESSION();

	RP_PROFILE_BEGIN_SESSION("Runtime", "ReptileProfile-Runtime-json");
	app->Run();
	RP_PROFILE_END_SESSION();

	RP_PROFILE_BEGIN_SESSION("Startup", "ReptileProfile-Shutdown-json");
	delete app;
	RP_PROFILE_END_SESSION();
}

#else
	#error Reptile only support on windows!
#endif
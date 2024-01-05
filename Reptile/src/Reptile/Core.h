#pragma once


#ifdef RP_PLATFORM_WINDOWS//只适用于windows
	#ifdef RP_BUILD_DLL//我们要构建这个DLL
		#define REPTILE_API __declspec(dllexport)
	#else
		#define REPTILE_API __declspec(dllimport)
	#endif
#else
	#error Reptile only support on windows!
#endif
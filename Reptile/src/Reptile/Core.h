#pragma once


#ifdef RP_PLATFORM_WINDOWS//只适用于windows
	#ifdef RP_BUILD_DLL//我们要构建这个DLL
		#define REPTILE_API __declspec(dllexport)//这个在reptile里
	#else
		#define REPTILE_API __declspec(dllimport)//这个在Sandbox里调用，不用在C++设置里添加RP_BUILD_DLL
	#endif
#else
	#error Reptile only support on windows!
#endif

#define BIT(x) (1 << x)
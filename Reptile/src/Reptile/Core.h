#pragma once


#ifdef RP_PLATFORM_WINDOWS//ֻ������windows
	#ifdef RP_BUILD_DLL//����Ҫ�������DLL
		#define REPTILE_API __declspec(dllexport)
	#else
		#define REPTILE_API __declspec(dllimport)
	#endif
#else
	#error Reptile only support on windows!
#endif
#pragma once


#ifdef RP_PLATFORM_WINDOWS//ֻ������windows
	#ifdef RP_BUILD_DLL//����Ҫ�������DLL
		#define REPTILE_API __declspec(dllexport)//�����reptile��
	#else
		#define REPTILE_API __declspec(dllimport)//�����Sandbox����ã�������C++���������RP_BUILD_DLL
	#endif
#else
	#error Reptile only support on windows!
#endif

#define BIT(x) (1 << x)
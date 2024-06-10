#pragma once

#include<memory>

#ifdef RP_PLATFORM_WINDOWS//ֻ������windows

#if RP_DYNAMIC_LINK
	#ifdef RP_BUILD_DLL//����Ҫ�������DLL
		#define REPTILE_API __declspec(dllexport)//�����reptile��
	#else
		#define REPTILE_API __declspec(dllimport)//�����Sandbox�����,������C++���������RP_BUILD_DLL
	#endif
#else 
	#define REPTILE_API
#endif
#else
	#error Reptile only support on windows!
#endif


#ifdef RP_ENABLE_ASSERTS
	#define RP_ASSERT(x, ...){if(!(x)){RP_ERROR("Assertion Failed:{0}",__VA__ARGS__);__debugbreak();}}
	#define RP_CORE_ASSERT(x, ...){if(!(x)){RP_CORE_ERROR("Assertion Failed:{0}",__VA__ARGS__);__debugbreak();}}
#else
	#define RP_ASSERT(x, ...)
	#define RP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define RP_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)


namespace Reptile
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}
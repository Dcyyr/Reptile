#pragma once

#include<chrono>
#include"Reptile/Core.h"

namespace Reptile {

	class REPTILE_API Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		void Timer::Reset()//重置
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		float Timer::Elapsed()//耗时
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}

		float Timer::ElapsedMillis()//所用时间
		{
			Elapsed() * 1000.0f;
		}


	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	}
}
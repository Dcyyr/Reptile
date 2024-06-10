#pragma once


namespace Reptile {

	class Timestep//这个可以让屏幕60RP，144RP看到同样的移动速率(w,a,s,d)，不会改变对应刷新率的每帧毫秒数
	{
	public:
		Timestep(float time = 0)
			:m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}
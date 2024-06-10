#pragma once


namespace Reptile {

	class Timestep//�����������Ļ60RP��144RP����ͬ�����ƶ�����(w,a,s,d)������ı��Ӧˢ���ʵ�ÿ֡������
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
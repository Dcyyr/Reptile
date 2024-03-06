#pragma once


namespace Reptile {

	class Timestep//�����������Ļ60hz��144hz����ͬ�����ƶ�����(w,a,s,d)������ı��Ӧˢ���ʵ�ÿ֡������
	{
	public:
		Timestep(float time = 0)
			:m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time; }
	private:
		float m_Time;
	};
}
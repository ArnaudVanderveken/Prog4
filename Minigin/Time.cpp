#include "Time.h"

using std::chrono::high_resolution_clock, std::chrono::milliseconds, std::chrono::duration;

dae::Time::Time()
{
	m_StartTime = high_resolution_clock::now();
	m_LastTime = m_StartTime;
}

void dae::Time::Update()
{
	m_CurrentTime = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;
	m_TotalTime = duration<float>(m_CurrentTime - m_StartTime).count();
}

float dae::Time::GetElapsedTime() const
{
	return m_DeltaTime;
}

float dae::Time::GetTotalTime() const
{
	return m_TotalTime;
}

float dae::Time::GetTimeToNextFrame() const
{
	float f = m_MsPerFrame / 1000 - m_DeltaTime;
	return f;
}

float dae::Time::GetMsPerFrame() const
{
	return m_MsPerFrame;
}

float dae::Time::GetFixedTimeStep() const
{
	return m_FixedTimeStep;
}



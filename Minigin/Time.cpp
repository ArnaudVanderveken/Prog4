#include "Time.h"

using namespace std::chrono;

void dae::Time::Update()
{
	m_LastFrameBeginTime = m_FrameBeginTime;
	m_FrameBeginTime = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_FrameBeginTime - m_LastFrameBeginTime).count();
	m_TotalTime = duration<float>(m_FrameBeginTime - m_StartTime).count();
}

float dae::Time::GetElapsedTime() const
{
	return m_DeltaTime;
}

float dae::Time::GetTotalTime() const
{
	return m_TotalTime;
}

std::chrono::duration<float> dae::Time::GetTimeToNextFrame()
{
	m_CurrentTime = high_resolution_clock::now();
	return duration<float>(m_TimePerFrame - duration<float>(m_CurrentTime - m_FrameBeginTime).count());
}

float dae::Time::GetFixedTimeStep() const
{
	return m_FixedTimeStep;
}

dae::Time::Time()
{
	m_StartTime = high_resolution_clock::now();
	m_FrameBeginTime = high_resolution_clock::now();
}


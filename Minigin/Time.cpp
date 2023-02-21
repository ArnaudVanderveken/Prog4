#include "Time.h"

using std::chrono::high_resolution_clock, std::chrono::milliseconds, std::chrono::duration;

void dae::Time::Init()
{
	m_StartTime = high_resolution_clock::now();
}

void dae::Time::Update()
{
	const auto currentTime = high_resolution_clock::now();
	m_DeltaTime = duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
	m_TotalTime += m_DeltaTime;
}

float dae::Time::GetElapsedTime() const
{
	return m_DeltaTime;
}

float dae::Time::GetTotalTime() const
{
	return m_TotalTime;
}

std::chrono::duration<float> dae::Time::GetTimeToNextFrame() const
{
	const float sleepTime = m_MsPerFrame - m_DeltaTime;
	return std::chrono::duration<float>(sleepTime > 0.0f ? sleepTime : 0.0f);
}

float dae::Time::GetMsPerFrame() const
{
	return m_MsPerFrame;
}

float dae::Time::GetFixedTimeStep() const
{
	return m_FixedTimeStep;
}

#pragma once
#include "Singleton.h"

#include <chrono>

namespace dae
{
	class Time final : public dae::Singleton<Time>
	{
	public:
		void Update();

		[[nodiscard]] float GetElapsedTime() const;
		[[nodiscard]] float GetTotalTime() const;
		[[nodiscard]] float GetTimeToNextFrame() const;
		[[nodiscard]] float GetMsPerFrame() const;
		[[nodiscard]] float GetFixedTimeStep() const;

	private:
		friend class Singleton<Time>;
		Time();

		const float m_MsPerFrame{ 1000.0f / 60.0f };
		const float m_FixedTimeStep{ 0.02f };

		std::chrono::steady_clock::time_point m_CurrentTime{}, m_LastTime{}, m_StartTime{};
		float m_TotalTime{};
		float m_DeltaTime{};
	};
}



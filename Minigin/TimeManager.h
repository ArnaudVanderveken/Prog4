#pragma once
#include "Singleton.h"

#include <chrono>

namespace dae
{
	class TimeManager final : public dae::Singleton<TimeManager>
	{
	public:
		void Update();

		[[nodiscard]] float GetElapsedTime() const;
		[[nodiscard]] float GetTotalTime() const;
		[[nodiscard]] std::chrono::duration<float> GetTimeToNextFrame();
		[[nodiscard]] float GetFixedTimeStep() const;

	private:
		friend class Singleton<TimeManager>;
		TimeManager();

		float m_FixedTimeStep{ 0.002f };
		float m_TimePerFrame{ 1.f / 144.f }; //0.0069444444444444

		float m_DeltaTime{};
		float m_TotalTime{};

		std::chrono::steady_clock::time_point m_StartTime{};
		std::chrono::steady_clock::time_point m_FrameBeginTime{};
		std::chrono::steady_clock::time_point m_LastFrameBeginTime{};
		std::chrono::steady_clock::time_point m_CurrentTime{};

	};
}



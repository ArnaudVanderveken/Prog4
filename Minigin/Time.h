#pragma once
#include "Singleton.h"

#include <chrono>

namespace dae
{
	class Time final : public dae::Singleton<Time>
	{
	public:
		void Init();
		void Update();

		[[nodiscard]] float GetElapsedTime() const;
		[[nodiscard]] float GetTotalTime() const;
		[[nodiscard]] std::chrono::duration<float> GetTimeToNextFrame() const;
		[[nodiscard]] float GetMsPerFrame() const;
		[[nodiscard]] float GetFixedTimeStep() const;

	private:
		friend class Singleton<Time>;
		Time() = default;

		const float m_MsPerFrame{ 1 / 60.0f };
		const float m_FixedTimeStep{ 0.02f };

		float m_DeltaTime{};
		float m_TotalTime{};
		std::chrono::steady_clock::time_point m_StartTime{};
		std::chrono::steady_clock::time_point m_LastTime{};
	};
}



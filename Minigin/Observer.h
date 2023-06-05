#pragma once

namespace dae
{
	template<typename... Args>
	class Observer {
	public:
		Observer() noexcept = default;
		virtual ~Observer() = default;

		Observer(const Observer& other) noexcept = delete;
		Observer(Observer&& other) noexcept = delete;

		Observer& operator=(const Observer& other) noexcept = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		virtual void HandleEvent(Args... args) = 0;
	};
}

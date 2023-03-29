#pragma once

#include "Event.h"

namespace dae
{
	class Observer
	{
	public:
		Observer() noexcept = default;
		virtual ~Observer() = default;

		Observer(const Observer& other) noexcept = delete;
		Observer& operator=(const Observer& other) noexcept = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		virtual void OnNotify(const Event& e) = 0;
		
	};
}

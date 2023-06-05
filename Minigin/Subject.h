#pragma once
#include "Observer.h"
#include <vector>

namespace dae
{
	template<typename... Args>
	class Subject final
	{
	public:
		Subject() noexcept = default;
		~Subject() = default;

		Subject(const Subject& other) noexcept = delete;
		Subject(Subject&& other) noexcept = delete;

		Subject& operator=(const Subject& other) noexcept = delete;
		Subject& operator=(Subject&& other) noexcept = delete;


		void AddObserver(Observer<Args...>* observer)
		{
			m_observers.push_back(observer);
		}

		void RemoveObserver(Observer<Args...>* observer)
		{
			m_observers.erase(std::remove(
				m_observers.begin(),
				m_observers.end(), observer),
				m_observers.end());
		}
		void Notify(Args... args) const
		{
			for (auto& observer : m_observers)
				observer->HandleEvent(args...);
		}

	private:
		std::vector<Observer<Args...>*> m_observers;
	};
}

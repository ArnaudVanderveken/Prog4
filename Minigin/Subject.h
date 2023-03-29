#pragma once

#include "Event.h"
#include <vector>

namespace dae
{
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		void Notify(const Event& e) const;

	private:
		/* DATA MEMBERS */

		std::vector<Observer*> m_pObservers;

		/* PRIVATE METHODS */

	};
}

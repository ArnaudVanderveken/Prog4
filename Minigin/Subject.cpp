#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.emplace_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	std::erase(m_pObservers, observer);
}

void dae::Subject::Notify(const Event& e) const
{
	for (const auto& observer : m_pObservers)
		observer->OnNotify(e);
}

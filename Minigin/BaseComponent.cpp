#include "BaseComponent.h"


void dae::BaseComponent::SetActive(bool newActive)
{
	m_IsActive = newActive;
}

bool dae::BaseComponent::IsActive() const
{
	return m_IsActive;
}

dae::GameObject* dae::BaseComponent::GetOwner() const
{
	return m_pOwner;
}

void dae::BaseComponent::SetOwner(GameObject* owner)
{
	m_pOwner = owner;
}

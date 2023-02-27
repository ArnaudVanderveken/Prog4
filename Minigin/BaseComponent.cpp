#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(dae::GameObject* parentGameObject) noexcept
{
	m_pGameObject = parentGameObject;
}

void dae::BaseComponent::SetActive(bool newActive)
{
	m_IsActive = newActive;
}

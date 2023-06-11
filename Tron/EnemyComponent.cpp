#include "EnemyComponent.h"

#include "GameObject.h"
#include "ServiceLocator.h"

dae::EnemyComponent::EnemyComponent(bool canShoot) noexcept
	: m_CanShoot(canShoot)
{
}

void dae::EnemyComponent::HandleEvent()
{
	GetOwner()->SetActive(false);
	ServiceLocator::GetGameManager()->CheckLevelCleared();
}

void dae::EnemyComponent::Update()
{
}

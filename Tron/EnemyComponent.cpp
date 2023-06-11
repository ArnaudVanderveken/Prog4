#include "EnemyComponent.h"

#include "GameObject.h"
#include "ServiceLocator.h"

dae::EnemyComponent::EnemyComponent(bool isRecognizer) noexcept
	: m_IsRecognizer(isRecognizer)
{
}

void dae::EnemyComponent::HandleEvent()
{
	GetOwner()->SetActive(false);
	ServiceLocator::GetGameManager()->CheckLevelCleared();
	scorePoints.Notify(m_IsRecognizer ? 200 : 100);
}

void dae::EnemyComponent::Update()
{

}

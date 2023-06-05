#include "LifeTrackerComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

dae::LifeTrackerComponent::LifeTrackerComponent(int trackedPlayerIndex) noexcept
	: m_TrackedPlayerIndex(trackedPlayerIndex)
{
}

void dae::LifeTrackerComponent::Init()
{
	m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
	if (m_pTextComponent)
		m_pTextComponent->SetText(std::string("Lives: ") + std::to_string(m_StartLives));
}

void dae::LifeTrackerComponent::Update()
{
}

void dae::LifeTrackerComponent::HandleEvent(int playerIndex)
{
	if (playerIndex == m_TrackedPlayerIndex && m_Lives > 0)
	{
		--m_Lives;
		if (m_pTextComponent)
			m_pTextComponent->SetText(std::string("Lives: ") + std::to_string(m_Lives));
	}
}

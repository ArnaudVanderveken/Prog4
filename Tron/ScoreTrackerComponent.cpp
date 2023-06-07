#include "ScoreTrackerComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

dae::ScoreTrackerComponent::ScoreTrackerComponent(int trackedPlayerIndex) noexcept
	: m_TrackedPlayerIndex(trackedPlayerIndex)
{
}

void dae::ScoreTrackerComponent::Init()
{
	m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
	if (m_pTextComponent)
		m_pTextComponent->SetText(std::string("Score: ") + std::to_string(m_Score));
}

void dae::ScoreTrackerComponent::Update()
{
}

void dae::ScoreTrackerComponent::HandleEvent(int playerIndex, int points)
{
	if (playerIndex == m_TrackedPlayerIndex)
	{
		m_Score += points;
		if (m_pTextComponent)
			m_pTextComponent->SetText(std::string("Score: ") + std::to_string(m_Score));
	}
}
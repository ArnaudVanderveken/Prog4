#include "LifeTrackerComponent.h"

#include "GameObject.h"
#include "TextComponent.h"


void dae::LifeTrackerComponent::Init()
{
	m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
	if (m_pTextComponent)
		m_pTextComponent->SetText(std::string("Lives: ") + std::to_string(m_StartLives));
}

void dae::LifeTrackerComponent::Update()
{
}

void dae::LifeTrackerComponent::HandleEvent()
{
	if (m_Lives > 0)
	{
		--m_Lives;
		if (m_pTextComponent)
			m_pTextComponent->SetText(std::string("Lives: ") + std::to_string(m_Lives));
	}
}

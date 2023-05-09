#include "FPSCounterComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "TimeManager.h"

#include <string>


void dae::FPSCounterComponent::Update()
{
	const float deltaTime = TimeManager::GetInstance().GetElapsedTime();
	m_Timer += deltaTime;
	++m_FrameCounter;

	if (m_Timer >= m_Delay)
	{
		const float fps{ static_cast<float>(m_FrameCounter) / m_Timer };
		sprintf_s(m_FpsText, "%.2f", fps);
		if (const auto text = GetOwner()->GetComponent<TextComponent>())
			text->SetText(std::string("FPS: ") + m_FpsText);

		m_Timer = 0.f;
		m_FrameCounter = 0;
	}
}

void dae::FPSCounterComponent::FixedUpdate()
{
}

void dae::FPSCounterComponent::Render() const
{
}

void dae::FPSCounterComponent::OnGUI()
{
}

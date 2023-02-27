#include "FPSCounterComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"
#include <iostream>

#include <string>

dae::FPSCounterComponent::FPSCounterComponent(dae::GameObject* attachedObj)
	: BaseComponent(attachedObj)
{
}

void dae::FPSCounterComponent::Update()
{
	const float deltaTime = Time::GetInstance().GetElapsedTime();
	m_Timer += deltaTime;

	if (m_Timer >= m_Delay)
	{
		m_Timer -= m_Delay;

		const float fps{ 1.0f / deltaTime };
		sprintf_s(m_FpsText, "%.2f", fps);
		if (const auto text = m_pGameObject->GetComponent<TextComponent>())
			text->SetText(std::string("FPS: ") + m_FpsText);
	}
}

void dae::FPSCounterComponent::FixedUpdate()
{
}

void dae::FPSCounterComponent::Render() const
{
}

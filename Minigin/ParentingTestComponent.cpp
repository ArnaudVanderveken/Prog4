#include "ParentingTestComponent.h"

#include "GameObject.h"
#include "Time.h"

dae::ParentingTestComponent::ParentingTestComponent(GameObject* owner)
	: BaseComponent(owner)
{
}

void dae::ParentingTestComponent::Update()
{
	m_Angle += float(m_Direction) * m_Speed * Time::GetInstance().GetElapsedTime();
	constexpr auto fullTurn = float(M_PI * 2);
	if (m_Angle > fullTurn)
		m_Angle -= fullTurn;
	m_pGameObject->SetLocalPosition({ cosf(m_Angle) * m_Radius, -sinf(m_Angle) * m_Radius, 0.f });
}

void dae::ParentingTestComponent::FixedUpdate()
{
}

void dae::ParentingTestComponent::Render() const
{
}

void dae::ParentingTestComponent::SetDirection(int dir)
{
	m_Direction = dir;
}

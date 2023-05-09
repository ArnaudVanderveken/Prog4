#include "ParentingTestComponent.h"

#include "GameObject.h"
#include "TimeManager.h"


void dae::ParentingTestComponent::Update()
{
	m_Angle += float(m_Direction) * m_Speed * TimeManager::GetInstance().GetElapsedTime();
	constexpr auto fullTurn = float(M_PI * 2);
	if (m_Angle > fullTurn)
		m_Angle -= fullTurn;
	GetOwner()->SetLocalPosition({ cosf(m_Angle) * m_Radius, -sinf(m_Angle) * m_Radius, 0.f });
}

void dae::ParentingTestComponent::FixedUpdate()
{
}

void dae::ParentingTestComponent::Render() const
{
}

void dae::ParentingTestComponent::OnGUI()
{
}

void dae::ParentingTestComponent::SetDirection(int dir)
{
	m_Direction = dir;
}

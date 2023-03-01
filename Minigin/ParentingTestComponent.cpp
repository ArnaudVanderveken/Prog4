#include "ParentingTestComponent.h"

#include "GameObject.h"
#include "Time.h"

dae::ParentingTestComponent::ParentingTestComponent(GameObject* owner)
	: BaseComponent(owner)
{
}

void dae::ParentingTestComponent::Update()
{
	auto newPos = m_pGameObject->GetLocalTransform().position;
	newPos.x += float(m_Direction) * m_Speed * Time::GetInstance().GetElapsedTime();
	m_pGameObject->SetLocalPosition(newPos);

	if (newPos.x >= m_XMax && m_Direction == 1)
		m_Direction = -1;
	else if (newPos.x < m_XMin && m_Direction == -1)
		m_Direction = 1;
}

void dae::ParentingTestComponent::FixedUpdate()
{
}

void dae::ParentingTestComponent::Render() const
{
}

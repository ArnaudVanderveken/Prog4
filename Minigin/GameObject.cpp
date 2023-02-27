#include "GameObject.h"

#include "BaseComponent.h"


dae::GameObject::~GameObject()
{
	for (const auto& component : m_Components)
		delete component;
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	m_Components.emplace_back(component);
}

void dae::GameObject::Update() const
{
	for (const auto& component : m_Components)
		component->Update();
}

void dae::GameObject::FixedUpdate() const
{
	for (const auto& component : m_Components)
		component->FixedUpdate();
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
		component->Render();
}

dae::Transform& dae::GameObject::GetTransform()
{
	return m_Transform;
}

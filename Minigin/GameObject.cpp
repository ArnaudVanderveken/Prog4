#include "GameObject.h"

#include "BaseComponent.h"


dae::GameObject::GameObject(bool startActive)
	: m_IsActive(startActive)
{
}

dae::GameObject::~GameObject()
{
	for (const auto& component : m_Components)
		delete component;
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	component->SetOwner(this);
	m_Components.emplace_back(component);
}

void dae::GameObject::Init() const
{
	for (const auto& component : m_Components)
		component->Init();
}

void dae::GameObject::Update() const
{
	if (m_IsActive)
		for (const auto& component : m_Components)
			if (component->IsActive())
				component->Update();
}

void dae::GameObject::FixedUpdate() const
{
	if (m_IsActive)
		for (const auto& component : m_Components)
			if (component->IsActive())
				component->FixedUpdate();
}

void dae::GameObject::LateUpdate() const
{
	if (m_IsActive)
		for (const auto& component : m_Components)
			if (component->IsActive())
				component->LateUpdate();
}

void dae::GameObject::Render() const
{
	if (m_IsActive)
		for (const auto& component : m_Components)
			if (component->IsActive())
				component->Render();
}

void dae::GameObject::OnGUI() const
{
	if (m_IsActive)
		for (const auto& component : m_Components)
			if (component->IsActive())
				component->OnGUI();
}

void dae::GameObject::MarkForDelete()
{
	m_MarkedForDelete = true;
	for (const auto& child : m_Children)
		child->MarkForDelete();
}

bool dae::GameObject::IsMarkedForDelete() const
{
	return m_MarkedForDelete;
}

const dae::Transform& dae::GameObject::GetLocalTransform() const
{
	return m_LocalTransform;
}

const dae::Transform& dae::GameObject::GetWorldTransform()
{
	if (m_DirtyWorldTransform)
		RebuildWorldTransform();

	return m_WorldTransform;
}

void dae::GameObject::SetLocalTransform(const Transform& transform)
{
	m_LocalTransform = transform;
	PropagateDirtyTransform();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_LocalTransform.position = position;
	PropagateDirtyTransform();
}

void dae::GameObject::SetLocalRotation(const glm::vec3& rotation)
{
	m_LocalTransform.rotation = rotation;
	PropagateDirtyTransform();
}

void dae::GameObject::SetLocalScale(const glm::vec3& scale)
{
	m_LocalTransform.scale = scale;
	PropagateDirtyTransform();
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldTransform)
{
	// Make sure world transform is up to date if kept
	if (keepWorldTransform && m_DirtyWorldTransform)
		RebuildWorldTransform();

	// Update parent
	if (m_Parent)
		m_Parent->RemoveChild(this);

	m_Parent = parent;

	if (m_Parent)
		m_Parent->AddChild(this);

	if (keepWorldTransform)
		RebuildLocalTransform();
	else
		m_DirtyWorldTransform = true; //Preserve local transform, world transform will be rebuilt on next GetWorldTransform.
}

void dae::GameObject::SetActive(bool active)
{
	m_IsActive = active;
}

bool dae::GameObject::IsActive() const
{
	return m_IsActive;
}

void dae::GameObject::PropagateDirtyTransform()
{
	m_DirtyWorldTransform = true;
	for (const auto child : m_Children)
		child->PropagateDirtyTransform();
}

void dae::GameObject::RebuildLocalTransform()
{
	if (m_Parent)
		m_LocalTransform = m_WorldTransform - m_Parent->GetWorldTransform();

	else
		m_LocalTransform = m_WorldTransform;

}

void dae::GameObject::RebuildWorldTransform()
{
	if (m_Parent)
		m_WorldTransform = m_Parent->GetWorldTransform() + m_LocalTransform;
	else
		m_WorldTransform = m_LocalTransform;
	m_DirtyWorldTransform = false;
}

void dae::GameObject::AddChild(GameObject* child)
{
	// Avoid adding child more than once
	if (std::ranges::find(m_Children, child) == m_Children.end())
		m_Children.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	std::erase(m_Children, child);
}

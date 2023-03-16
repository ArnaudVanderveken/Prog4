#include "RenderComponent.h"

#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(const std::string& fileName)
{
	if (!fileName.empty())
		m_TexturePtr = ResourceManager::GetInstance().LoadTexture(fileName);
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::FixedUpdate()
{
}

void dae::RenderComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_TexturePtr, GetOwner()->GetWorldTransform().position.x, GetOwner()->GetWorldTransform().position.y);
}

void dae::RenderComponent::OnGUI()
{
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_TexturePtr = texture;
}
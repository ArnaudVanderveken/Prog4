#include "RenderComponent.h"

#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(const std::string& fileName, const glm::vec2& offset, float angle)
	: m_Offset(offset)
	, m_Angle(angle)
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
	//Renderer::GetInstance().RenderTexture(*m_TexturePtr, GetOwner()->GetWorldTransform().position.x, GetOwner()->GetWorldTransform().position.y);
	Renderer::GetInstance().RenderTexture(*m_TexturePtr, GetOwner()->GetWorldTransform().position.x, GetOwner()->GetWorldTransform().position.y, m_Offset, m_Angle);
}

void dae::RenderComponent::OnGUI()
{
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_TexturePtr = texture;
}

void dae::RenderComponent::SetOffset(const glm::vec2& offset)
{
	m_Offset = offset;
}

void dae::RenderComponent::SetAngle(float angle)
{
	m_Angle = angle;
}

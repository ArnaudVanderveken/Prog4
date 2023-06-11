#include "BulletManager.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"

dae::BulletManager::BulletManager() noexcept
	: m_pPlayerBulletTexture(ResourceManager::GetInstance().LoadTexture("Sprites/BulletPlayer.png"))
	, m_pNPCBulletTexture(ResourceManager::GetInstance().LoadTexture("Sprites/BulletNPC.png"))
{
	m_BulletObjects.reserve(PRELOAD_COUNT);
	m_BulletComponents.reserve(PRELOAD_COUNT);
	m_RenderComponents.reserve(PRELOAD_COUNT);

	for (uint8_t i{}; i < PRELOAD_COUNT; ++i)
		CreateNewBullet();
}

void dae::BulletManager::SpawnBullet(const glm::vec2& position, BulletComponent::Type type, const glm::vec2& direction) const
{
	size_t i{};
	do 
	{
		if (!m_BulletObjects[i]->IsActive())
			break;
		++i;
	} while (i < m_BulletObjects.size());
	if (i == m_BulletObjects.size())
		return;

	m_BulletComponents[i]->SetPosition(position);
	m_BulletComponents[i]->SetDirection(direction);
	m_BulletComponents[i]->SetType(type);
	m_RenderComponents[i]->SetTexture(type == BulletComponent::Type::Enemy ? m_pNPCBulletTexture : m_pPlayerBulletTexture);
	m_BulletComponents[i]->Reset();

	m_BulletObjects[i]->SetActive(true);
}

void dae::BulletManager::RemoveBullet(uint16_t bulletIndex) const
{
	m_BulletObjects[bulletIndex]->SetActive(false);
}

void dae::BulletManager::ResetBullets() const
{
	for (size_t i{}; i < m_BulletObjects.size(); ++i)
		m_BulletObjects[i]->SetActive(false);
}

const std::vector<std::shared_ptr<dae::GameObject>>& dae::BulletManager::GetBullets() const
{
	return m_BulletObjects;
}

const std::vector<dae::BulletComponent*>& dae::BulletManager::GetBulletComponents() const
{
	return m_BulletComponents;
}

void dae::BulletManager::CreateNewBullet()
{
	const auto index = static_cast<uint16_t>(m_BulletObjects.size());
	m_BulletObjects.emplace_back(std::make_shared<GameObject>(false));
	m_BulletComponents.emplace_back(new BulletComponent(index));
	m_RenderComponents.emplace_back(new RenderComponent(m_pNPCBulletTexture, { 0.5f, 0.5f }));
	m_BulletObjects[index]->AddComponent(m_BulletComponents[index]);
	m_BulletObjects[index]->AddComponent(m_RenderComponents[index]);
}

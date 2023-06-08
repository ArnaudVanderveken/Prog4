#include "BulletManager.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"

dae::BulletManager::BulletManager(Scene& scene) noexcept
	: m_Scene(scene)
	, m_pPlayerBulletTexture(ResourceManager::GetInstance().LoadTexture("Sprites/BulletPlayer.png"))
	, m_pNPCBulletTexture(ResourceManager::GetInstance().LoadTexture("Sprites/BulletNPC.png"))
{
	m_BulletObjects.reserve(PRELOAD_COUNT);
	m_BulletComponents.reserve(PRELOAD_COUNT);
	m_RenderComponents.reserve(PRELOAD_COUNT);
	m_ActiveBullets.reserve(PRELOAD_COUNT);

	for (uint8_t i{}; i < PRELOAD_COUNT; ++i)
		CreateNewBullet();
}

void dae::BulletManager::SpawnBullet(const glm::vec2& position, BulletComponent::Type type, const glm::vec2& direction)
{
	size_t i{};
	do 
	{
		if (!m_ActiveBullets[i])
			break;
		++i;
	} while (i < m_ActiveBullets.size());
	if (i == m_ActiveBullets.size())
		CreateNewBullet();

	m_BulletComponents[i]->SetPosition(position);
	m_BulletComponents[i]->SetDirection(direction);
	m_BulletComponents[i]->SetType(type);
	m_BulletComponents[i]->Reset();

	m_BulletObjects[i]->SetActive(true);
	m_ActiveBullets[i] = true;
}

void dae::BulletManager::RemoveBullet(uint16_t bulletIndex)
{
	m_BulletObjects[bulletIndex]->SetActive(false);
	m_ActiveBullets[bulletIndex] = false;
}

void dae::BulletManager::CreateNewBullet()
{
	const auto index = static_cast<uint16_t>(m_BulletObjects.size());
	m_ActiveBullets.emplace_back(false);
	m_BulletObjects.emplace_back(std::make_shared<GameObject>(false));
	m_BulletComponents.emplace_back(new BulletComponent(index));
	m_RenderComponents.emplace_back(new RenderComponent(m_pNPCBulletTexture, { 0.5f, 0.5f }));
	m_BulletObjects[index]->AddComponent(m_BulletComponents[index]);
	m_BulletObjects[index]->AddComponent(m_RenderComponents[index]);

	m_Scene.Add(m_BulletObjects[index]);
}

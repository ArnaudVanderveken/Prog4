#include "LevelManager.h"

#include "GameObject.h"
#include "LevelComponent.h"
#include "Scene.h"

dae::LevelManager::LevelManager() noexcept
{
	m_LevelObjects.reserve(LEVEL_COUNT);
	m_LevelComponents.reserve(LEVEL_COUNT);

	for (uint8_t i{}; i < LEVEL_COUNT; ++i)
	{
		m_LevelObjects.emplace_back(std::make_shared<GameObject>(false));
		std::string filename = "../Data/Level" + std::to_string(i+1) + ".bin";
		m_LevelComponents.emplace_back(new LevelComponent(filename));
		m_LevelObjects[i]->AddComponent(m_LevelComponents[i]);
		m_LevelObjects[i]->SetLocalPosition(LEVEL_POSITION);
	}

}

dae::LevelComponent* dae::LevelManager::GetCurrentSceneComponent() const
{
	return m_LevelComponents[m_CurrentLevel];
}

const std::shared_ptr<dae::GameObject>& dae::LevelManager::GetLevelObject(uint8_t levelIndex) const
{
	assert(levelIndex < m_LevelObjects.size());
	return m_LevelObjects[levelIndex];
}

void dae::LevelManager::LoadLevel(uint8_t index)
{
	m_CurrentLevel = index;
	m_LevelObjects[m_CurrentLevel]->SetActive(true);
}

void dae::LevelManager::UnloadLevel(uint8_t index)
{
	m_CurrentLevel = index;
	m_LevelObjects[m_CurrentLevel]->SetActive(false);
}

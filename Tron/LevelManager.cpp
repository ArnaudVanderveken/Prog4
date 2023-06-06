#include "LevelManager.h"

#include "GameObject.h"
#include "LevelComponent.h"
#include "Scene.h"

dae::LevelManager::LevelManager(Scene& scene) noexcept
	: m_Scene(scene)
{
	static constexpr uint8_t LEVEL_COUNT{3};
	m_LevelObjects.reserve(LEVEL_COUNT);
	m_LevelComponents.reserve(LEVEL_COUNT);

	for (uint8_t i{}; i < LEVEL_COUNT; ++i)
	{
		m_LevelObjects.emplace_back(std::make_shared<GameObject>());
		std::string filename = "../Data/Level" + std::to_string(i+1) + ".bin";
		m_LevelComponents.emplace_back(new LevelComponent(filename));
		m_LevelObjects[i]->AddComponent(m_LevelComponents[i]);
		m_LevelObjects[i]->SetLocalPosition({ 88, 0, 0 });
	}
	m_Scene.Add(m_LevelObjects[m_CurrentLevel]);
}

dae::LevelComponent* dae::LevelManager::GetCurrentSceneComponent() const
{
	return m_LevelComponents[m_CurrentLevel];
}

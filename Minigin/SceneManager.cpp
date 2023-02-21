#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update() const
{
	for(auto& scene : m_scenes)
		scene->Update();
}

void dae::SceneManager::FixedUpdate() const
{
	for (auto& scene : m_scenes)
		scene->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
		scene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

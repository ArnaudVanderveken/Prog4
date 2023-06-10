#include "SceneManager.h"

#include <cassert>

#include "Scene.h"

void dae::SceneManager::Update()
{
	if (m_SceneChange)
	{
		m_SceneChange = false;
		m_ActiveScene = m_Scenes[m_NewScene];
	}
	m_ActiveScene->Update();
}

void dae::SceneManager::FixedUpdate() const
{
	m_ActiveScene->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	m_ActiveScene->Render();
}

void dae::SceneManager::OnGui() const
{
	m_ActiveScene->OnGUI();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::SetActiveScene(uint8_t sceneIndex)
{
	assert(sceneIndex < m_Scenes.size());
	m_NewScene = sceneIndex;
	m_SceneChange = true;
}

void dae::SceneManager::Init()
{
	m_ActiveScene = m_Scenes[0];
	for (const auto& scene : m_Scenes)
		scene->Init();
}

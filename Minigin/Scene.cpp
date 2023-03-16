#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	std::erase(m_Objects, object);
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Update()
{
	for(const auto& object : m_Objects)
		object->Update();

	for (const auto& object : m_Objects)
		if (object->IsMarkedForDelete())
			m_TrashBin.emplace_back(object);

	for (const auto& object : m_TrashBin)
		std::erase(m_Objects, object);
	
	m_TrashBin.clear();
}

void Scene::FixedUpdate() const
{
	for (const auto& object : m_Objects)
		object->FixedUpdate();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
		object->Render();
}

void Scene::OnGUI() const
{
	for (const auto& object : m_Objects)
		object->OnGUI();
}


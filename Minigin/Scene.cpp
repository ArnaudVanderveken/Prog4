#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	std::erase(m_objects, object);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update() const
{
	for(const auto& object : m_objects)
		object->Update();
}

void Scene::FixedUpdate() const
{
	for (const auto& object : m_objects)
		object->FixedUpdate();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
		object->Render();
}


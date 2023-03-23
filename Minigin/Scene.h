#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Remove(const std::shared_ptr<GameObject>& object);
		void RemoveAll();

		void Init() const;

		void Update();
		void FixedUpdate() const;
		void Render() const;

		void OnGUI() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};
		std::vector <std::shared_ptr<GameObject>> m_TrashBin{};

		static unsigned int m_IdCounter; 
	};

}

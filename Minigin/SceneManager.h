#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetActiveScene(uint8_t sceneIndex);

		void Init();

		void Update();
		void FixedUpdate() const;
		void Render() const;

		void OnGui() const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
		bool m_SceneChange{};
		uint8_t m_NewScene{};
	};
}

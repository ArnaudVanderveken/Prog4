#pragma once
#include <memory>
#include <vector>

namespace dae
{
	class GameObject;
	class Scene;
	class LevelComponent;
	class LevelManager final
	{
	public:
		LevelManager(Scene& scene) noexcept;
		~LevelManager() = default;

		LevelManager(const LevelManager& other) noexcept = delete;
		LevelManager(LevelManager&& other) noexcept = delete;
		LevelManager& operator=(const LevelManager& other) noexcept = delete;
		LevelManager& operator=(LevelManager&& other) noexcept = delete;

		[[nodiscard]] LevelComponent* GetCurrentSceneComponent() const;

	private:
		/* DATA MEMBERS */

		Scene& m_Scene;

		std::vector<std::shared_ptr<GameObject>> m_LevelObjects;
		std::vector<LevelComponent*> m_LevelComponents;

		uint8_t m_CurrentLevel{};

		/* PRIVATE METHODS */



	};
}



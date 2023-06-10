#pragma once
#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
	class Scene;
	class LevelComponent;
	class LevelManager final
	{
	public:
		LevelManager() noexcept;
		~LevelManager() = default;

		LevelManager(const LevelManager& other) noexcept = delete;
		LevelManager(LevelManager&& other) noexcept = delete;
		LevelManager& operator=(const LevelManager& other) noexcept = delete;
		LevelManager& operator=(LevelManager&& other) noexcept = delete;

		[[nodiscard]] LevelComponent* GetCurrentSceneComponent() const;
		[[nodiscard]] const std::shared_ptr<GameObject>& GetLevelObject(uint8_t levelIndex) const;

		void LoadLevel(uint8_t index);
		void UnloadLevel(uint8_t index);

	private:
		/* DATA MEMBERS */

		static constexpr glm::vec3 LEVEL_POSITION{ 88.0f, 0.0f, 0.0f };
		static constexpr uint8_t LEVEL_COUNT{ 3 };

		std::vector<std::shared_ptr<GameObject>> m_LevelObjects{};
		std::vector<LevelComponent*> m_LevelComponents{};

		uint8_t m_CurrentLevel{};

		/* PRIVATE METHODS */


	};
}



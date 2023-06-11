#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "BulletComponent.h"


namespace dae
{
	class GameObject;
	class RenderComponent;
	class Scene;
	class Texture2D;
	
	class BulletManager final
	{
	public:
		BulletManager() noexcept;
		~BulletManager() = default;

		BulletManager(const BulletManager& other) noexcept = delete;
		BulletManager(BulletManager&& other) noexcept = delete;
		BulletManager& operator=(const BulletManager& other) noexcept = delete;
		BulletManager& operator=(BulletManager&& other) noexcept = delete;

		void SpawnBullet(const glm::vec2& position, BulletComponent::Type type, const glm::vec2& direction);
		void RemoveBullet(uint16_t bulletIndex);

		void ResetBullets();

		[[nodiscard]] const std::vector<std::shared_ptr<GameObject>>& GetBullets() const;
		[[nodiscard]] const std::vector<BulletComponent*>& GetBulletComponents() const;

	private:
		/* DATA MEMBERS */

		static constexpr uint8_t PRELOAD_COUNT{ 64 };

		std::shared_ptr<Texture2D> m_pPlayerBulletTexture{};
		std::shared_ptr<Texture2D> m_pNPCBulletTexture{};

		std::vector<std::shared_ptr<GameObject>> m_BulletObjects{};
		std::vector<BulletComponent*> m_BulletComponents{};
		std::vector<RenderComponent*> m_RenderComponents{};
		std::vector<bool> m_ActiveBullets{};

		/* PRIVATE METHODS */

		void CreateNewBullet();

	};
}

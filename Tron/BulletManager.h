#pragma once

#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
	class BulletManager final
	{
	public:
		BulletManager() noexcept = default;
		~BulletManager() = default;

		BulletManager(const BulletManager& other) noexcept = delete;
		BulletManager(BulletManager&& other) noexcept = delete;
		BulletManager& operator=(const BulletManager& other) noexcept = delete;
		BulletManager& operator=(BulletManager&& other) noexcept = delete;

		void SpawnBullet(const glm::vec2)

	private:
		/* DATA MEMBERS */


		/* PRIVATE METHODS */



	};
}

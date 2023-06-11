#pragma once

#include "BaseComponent.h"
#include "Subject.h"

#include <glm/glm.hpp>

namespace dae
{
	class BulletCollisionChecker final : public BaseComponent
	{
	public:
		BulletCollisionChecker() noexcept = default;
		~BulletCollisionChecker() override = default;

		BulletCollisionChecker(const BulletCollisionChecker& other) noexcept = delete;
		BulletCollisionChecker(BulletCollisionChecker&& other) noexcept = delete;
		BulletCollisionChecker& operator=(const BulletCollisionChecker& other) noexcept = delete;
		BulletCollisionChecker& operator=(BulletCollisionChecker&& other) noexcept = delete;

		void SetRules(bool p1, bool p2, bool enemy);

		Subject<> wasHit;

	protected:
		void Update() override {}
		void LateUpdate() override;

	private:
		/* DATA MEMBERS */

		bool m_IsHitByP1{};
		bool m_IsHitByP2{};
		bool m_IsHitByEnemy{};

		/* PRIVATE METHODS */

		static bool IsColliding(const glm::vec2& tankPos, const glm::vec2& bulletPos);
		static constexpr float TANK_EXTENT{ 16.0f };
	};
}

#pragma once
#include "BaseComponent.h"
#include "Subject.h"

#include <glm/glm.hpp>

namespace dae
{
    class EnemyComponent final : public BaseComponent, public Observer<>
    {
    public:
	    EnemyComponent(bool isRecognizer) noexcept;
	    ~EnemyComponent() override = default;

	    EnemyComponent(const EnemyComponent& other) noexcept = delete;
	    EnemyComponent(EnemyComponent&& other) noexcept = delete;
	    EnemyComponent& operator=(const EnemyComponent& other) noexcept = delete;
	    EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;

		void HandleEvent() override;

		Subject<int> scorePoints;

    protected:
		void Update() override;
		void LateUpdate() override;

    private:
	    /* DATA MEMBERS */

		GameObject* m_pTarget{};

		bool m_IsRecognizer{};
		bool m_TargetInSight{};

		static constexpr float FIRE_COOLDOWN{ 1.0f };
		float m_FireCooldown{ FIRE_COOLDOWN };

		int m_FireSound;

	    /* PRIVATE METHODS */

		bool CheckIsInSight(const glm::vec3& pos);

    };
}

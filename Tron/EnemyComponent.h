#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
    class EnemyComponent final : public BaseComponent, public Observer<>
    {
    public:
	    EnemyComponent(bool canShoot) noexcept;
	    ~EnemyComponent() override = default;

	    EnemyComponent(const EnemyComponent& other) noexcept = delete;
	    EnemyComponent(EnemyComponent&& other) noexcept = delete;
	    EnemyComponent& operator=(const EnemyComponent& other) noexcept = delete;
	    EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;

		void HandleEvent() override;

    protected:
		void Update() override;

    private:
	    /* DATA MEMBERS */

		bool m_CanShoot{};

	    /* PRIVATE METHODS */



    };
}

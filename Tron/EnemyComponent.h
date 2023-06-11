#pragma once
#include "BaseComponent.h"
#include "Subject.h"

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

    private:
	    /* DATA MEMBERS */

		bool m_IsRecognizer{};

	    /* PRIVATE METHODS */



    };
}

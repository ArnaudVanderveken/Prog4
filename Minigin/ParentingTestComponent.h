#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ParentingTestComponent : public dae::BaseComponent
	{
	public:
		ParentingTestComponent(GameObject* owner);
		~ParentingTestComponent() override = default;
		ParentingTestComponent(const ParentingTestComponent& other) = delete;
		ParentingTestComponent& operator=(const ParentingTestComponent& other) noexcept = delete;
		ParentingTestComponent(ParentingTestComponent&& other) = delete;
		ParentingTestComponent& operator=(ParentingTestComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetDirection(int dir);

	private:
		float m_Angle{};
		float m_Radius{ 50.f };
		float m_Speed{ 3.14159278359596f };
		int m_Direction{ 1 };
	};
}



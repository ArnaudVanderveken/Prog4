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

	private:
		float m_XMin{ 200.0f };
		float m_XMax{ 400.0f };
		float m_Speed{ 100.0f };
		int m_Direction{ 1 };
	};
}



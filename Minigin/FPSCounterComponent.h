#pragma once
#include "BaseComponent.h"


namespace dae
{
	class Font;

	class FPSCounterComponent final : public BaseComponent
	{
	public:
		FPSCounterComponent(GameObject* attachedObj);
		~FPSCounterComponent() override = default;
		FPSCounterComponent(const FPSCounterComponent& other) = delete;
		FPSCounterComponent& operator=(const FPSCounterComponent& other) noexcept = delete;
		FPSCounterComponent(FPSCounterComponent&& other) = delete;
		FPSCounterComponent& operator=(FPSCounterComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnGUI() override;

	private:
		char m_FpsText[16]{};
		const float m_Delay{ .5f };
		float m_Timer{};
		unsigned short m_FrameCounter{};
	};
}


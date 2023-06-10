#pragma once
#include "BaseComponent.h"
#include "Observer.h"


namespace dae
{
	class TextComponent;
	class LifeTrackerComponent final : public BaseComponent, public Observer<>
	{
	public:
		explicit LifeTrackerComponent() noexcept = default;
		~LifeTrackerComponent() override = default;

		LifeTrackerComponent(const LifeTrackerComponent& other) noexcept = delete;
		LifeTrackerComponent& operator=(const LifeTrackerComponent& other) noexcept = delete;
		LifeTrackerComponent(LifeTrackerComponent&& other) noexcept = delete;
		LifeTrackerComponent& operator=(LifeTrackerComponent&& other) noexcept = delete;

		void Init() override;
		void Update() override;

		void HandleEvent() override;

	private:
		/* DATA MEMBERS */

		int m_TrackedPlayerIndex{};
		const int m_StartLives{ 3 };
		int m_Lives{ m_StartLives };

		TextComponent* m_pTextComponent{};

		/* PRIVATE METHODS */
		
	};
}


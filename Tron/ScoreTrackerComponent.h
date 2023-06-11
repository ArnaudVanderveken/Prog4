#pragma once
#include "BaseComponent.h"
#include "Observer.h"


namespace dae
{
	class TextComponent;
	class ScoreTrackerComponent : public BaseComponent, public Observer<int>
	{
	public:
		explicit ScoreTrackerComponent() noexcept = default;
		~ScoreTrackerComponent() override = default;

		ScoreTrackerComponent(const ScoreTrackerComponent& other) = delete;
		ScoreTrackerComponent& operator=(const ScoreTrackerComponent& other) noexcept = delete;
		ScoreTrackerComponent(ScoreTrackerComponent&& other) = delete;
		ScoreTrackerComponent& operator=(ScoreTrackerComponent&& other) noexcept = delete;

		void Init() override;
		void Update() override;

		void Reset();
		[[nodiscard]] int GetScore() const;

		void HandleEvent(int points) override;

	private:
		/* DATA MEMBERS */

		int m_Score{};

		TextComponent* m_pTextComponent{};

		/* PRIVATE METHODS */


	};
}


#pragma once

#include "BaseComponent.h"
#include "Observer.h"
#include "Subject.h"


namespace dae
{
	class TextComponent;
	class ScoreTrackerComponent : public BaseComponent, public Observer, public Subject
	{
	public:
		explicit ScoreTrackerComponent(int trackedPlayerIndex) noexcept;
		~ScoreTrackerComponent() override = default;

		ScoreTrackerComponent(const ScoreTrackerComponent& other) = delete;
		ScoreTrackerComponent& operator=(const ScoreTrackerComponent& other) noexcept = delete;
		ScoreTrackerComponent(ScoreTrackerComponent&& other) = delete;
		ScoreTrackerComponent& operator=(ScoreTrackerComponent&& other) noexcept = delete;

		void Init() override;
		void Update() override;

		void OnNotify(const Event& e) override;

	private:
		/* DATA MEMBERS */

		int m_TrackedPlayerIndex{};
		int m_Score{};

		const int m_MinScoreWin{ 500 };

		TextComponent* m_pTextComponent{};

		/* PRIVATE METHODS */


	};
}


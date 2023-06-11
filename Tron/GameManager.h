#pragma once

#include <array>
#include <memory>
#include <vector>

namespace dae
{
	class BulletCollisionChecker;
	class EnemyComponent;
	class GameObject;
	class LifeTrackerComponent;
	class PlayerControllerComponent;
	class ScoreTrackerComponent;
	class TextComponent;
	class GameManager
	{
	public:
		enum class State
		{
			MainMenu,
			Level1,
			Level2,
			Level3,
			PauseMenu,
			EndScreen,
			LeaderBoard
		};

		enum class GameMode
		{
			SinglePlayer,
			Coop,
			Versus,
			SIZE
		};

		static constexpr uint8_t ENEMY_PRELOAD{ 5 };

		GameManager() noexcept;
		~GameManager() = default;

		GameManager(const GameManager& other) noexcept = delete;
		GameManager(GameManager&& other) noexcept = delete;
		GameManager& operator=(const GameManager& other) noexcept = delete;
		GameManager& operator=(GameManager&& other) noexcept = delete;

		[[nodiscard]] GameMode GetGamemode() const;

		void ToggleGamemode();
		void PauseGame();
		void UnpauseGame();
		void SkipLevel();

		void SetState(State state, bool skipExit = false);
		void ResetTanks() const;
		void CheckLevelCleared();
		void EndGame();

		void RegisterGamemodeText(TextComponent* pTextComponent);

		[[nodiscard]] const std::shared_ptr<GameObject>& GetP1Tank() const;
		[[nodiscard]] const std::shared_ptr<GameObject>& GetP2Tank() const;
		[[nodiscard]] const std::array<std::shared_ptr<GameObject>, ENEMY_PRELOAD>& GetEnemyTanks() const;
		[[nodiscard]] const std::array<std::shared_ptr<GameObject>, ENEMY_PRELOAD>& GetRecognizerTanks() const;

		[[nodiscard]] const std::shared_ptr<GameObject>& GetLifeCounter() const;
		[[nodiscard]] const std::shared_ptr<GameObject>& GetScoreCounter() const;

	private:
		/* DATA MEMBERS */

		GameMode m_Gamemode{};
		State m_State{};
		State m_PrePauseState{};
		bool m_ResetLevel{ true };

		int m_MainMenuSound{}, m_BackgroundSound{}, m_FailSound{};

		std::shared_ptr<GameObject> m_pP1Tank{};
		PlayerControllerComponent* m_pP1Component{};
		BulletCollisionChecker* m_pP1CollisionChecker{};

		std::shared_ptr<GameObject> m_pP2Tank{};
		PlayerControllerComponent* m_pP2Component{};
		BulletCollisionChecker* m_pP2CollisionChecker{};

		std::array<std::shared_ptr<GameObject>, ENEMY_PRELOAD> m_pEnemyTanks{};
		std::array<EnemyComponent*, ENEMY_PRELOAD> m_pEnemyTankComponents{};
		std::array<BulletCollisionChecker*, ENEMY_PRELOAD> m_pEnemyTankCollisionCheckers{};

		std::array<std::shared_ptr<GameObject>, ENEMY_PRELOAD> m_pRecognizerTanks{};
		std::array<EnemyComponent*, ENEMY_PRELOAD> m_pRecognizerTankComponents{};
		std::array<BulletCollisionChecker*, ENEMY_PRELOAD> m_pRecognizerTankCollisionCheckers{};

		std::shared_ptr<GameObject> m_pScoreCounter{};
		ScoreTrackerComponent* m_pScoreCounterComponent{};
		std::shared_ptr<GameObject> m_pLifeCounter{};
		LifeTrackerComponent* m_pLifeCounterComponent{};

		TextComponent* m_pGamemodeText{};

		/* PRIVATE METHODS */

		void OnStateEnter();
		void OnStateExit();

		void BindMainMenuCommands();
		void BindLevelCommands();
		void BindPauseCommands();
		void BindEndScreenCommands();
		void BindLeaderBoardCommands();

		void UpdateGamemodeText();
		void ApplyGamemode();
	};
}

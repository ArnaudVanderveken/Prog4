#pragma once

#include <string>

namespace dae
{
	class TextComponent;
	class LeaderboardManager
	{
	public:
		LeaderboardManager() noexcept = default;
		~LeaderboardManager() = default;

		LeaderboardManager(const LeaderboardManager& other) noexcept = delete;
		LeaderboardManager(LeaderboardManager&& other) noexcept = delete;
		LeaderboardManager& operator=(const LeaderboardManager& other) noexcept = delete;
		LeaderboardManager& operator=(LeaderboardManager&& other) noexcept = delete;

		void SetP1TextComponent(TextComponent* textComponent);
		void SetP2TextComponent(TextComponent* textComponent);
		void SetBoardTextComponent(TextComponent* textComponent);

		void UpdateBoardText() const;
		void UpdateP1Text() const;
		void UpdateP2Text() const;

		void AppendLetter(char c);
		void PopLetter();
		void Enter();

	private:
		/* DATA MEMBERS */

		bool m_AppendToP2{};
		std::string m_P1Name{};
		std::string m_P2Name{};

		TextComponent* m_pP1TextComponent{};
		TextComponent* m_pP2TextComponent{};
		TextComponent* m_pBoardTextComponent{};

		/* PRIVATE METHODS */
		

	};
}

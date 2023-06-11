#pragma once

#include <string>
#include <vector>

namespace dae
{
	class TextComponent;
	class LeaderboardManager
	{
	public:
		LeaderboardManager() noexcept;
		~LeaderboardManager();

		LeaderboardManager(const LeaderboardManager& other) noexcept = delete;
		LeaderboardManager(LeaderboardManager&& other) noexcept = delete;
		LeaderboardManager& operator=(const LeaderboardManager& other) noexcept = delete;
		LeaderboardManager& operator=(LeaderboardManager&& other) noexcept = delete;

		void SetP1TextComponent(TextComponent* textComponent);
		void SetP2TextComponent(TextComponent* textComponent);
		void SetBoardTextComponent(TextComponent* textComponent, uint8_t line);

		void UpdateBoardText() const;
		void UpdateP1Text() const;
		void UpdateP2Text() const;

		void AppendLetter(char c);
		void PopLetter();
		void Enter();

		static constexpr uint8_t LINES{ 10 };

	private:
		/* DATA MEMBERS */

		struct Entry
		{
			std::string p1{};
			std::string p2{};
			int score{};
		};

		bool m_AppendToP2{};
		std::string m_P1Name{};
		std::string m_P2Name{};
		std::vector<Entry> m_SoloBoard{};
		std::vector<Entry> m_CoopBoard{};
		std::vector<Entry> m_VersusBoard{};

		TextComponent* m_pP1TextComponent{};
		TextComponent* m_pP2TextComponent{};
		std::vector<TextComponent*> m_pBoardTextComponents{};

		/* PRIVATE METHODS */

		void LoadFromFile();
		void WriteToFile() const;
		void CheckNewEntry();
	};
}

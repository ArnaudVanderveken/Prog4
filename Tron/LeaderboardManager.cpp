#include "LeaderboardManager.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "GameObject.h"
#include "ScoreTrackerComponent.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

dae::LeaderboardManager::LeaderboardManager() noexcept
{
	m_SoloBoard.resize(LINES);
	m_CoopBoard.resize(LINES);
	m_VersusBoard.resize(LINES);
	m_pBoardTextComponents.resize(LINES);

	LoadFromFile();
}

dae::LeaderboardManager::~LeaderboardManager()
{
	WriteToFile();
}

void dae::LeaderboardManager::SetP1TextComponent(TextComponent* textComponent)
{
	m_pP1TextComponent = textComponent;
}

void dae::LeaderboardManager::SetP2TextComponent(TextComponent* textComponent)
{
	m_pP2TextComponent = textComponent;
}

void dae::LeaderboardManager::SetBoardTextComponent(TextComponent* textComponent, uint8_t line)
{
	m_pBoardTextComponents[line] = textComponent;
}

void dae::LeaderboardManager::UpdateBoardText() const
{
	switch (ServiceLocator::GetGameManager()->GetGamemode())
	{
	case GameManager::GameMode::SinglePlayer:
		for (uint8_t i{}; i < LINES; ++i)
		{
			if (m_SoloBoard[i].p1.empty())
				m_pBoardTextComponents[i]->SetText(std::to_string(i + 1) + ". ");
			else
				m_pBoardTextComponents[i]->SetText(std::to_string(i + 1) + ". " + m_SoloBoard[i].p1 + ": " + std::to_string(m_SoloBoard[i].score));
		}
		break;

	case GameManager::GameMode::Coop:
		for (uint8_t i{}; i < LINES; ++i)
		{
			if (m_CoopBoard[i].p1.empty())
				m_pBoardTextComponents[i]->SetText(std::to_string(i + 1) + ". ");
			else
				m_pBoardTextComponents[i]->SetText(std::to_string(i + 1) + ". " + m_CoopBoard[i].p1 + " & " + m_CoopBoard[i].p2 + ": " + std::to_string(m_CoopBoard[i].score));
		}
		break;

	case GameManager::GameMode::Versus:
		for (uint8_t i{}; i < LINES; ++i)
		{
			if (m_VersusBoard[i].p1.empty())
				m_pBoardTextComponents[i]->SetText(std::to_string(i + 1) + ". ");
			else
				m_pBoardTextComponents[i]->SetText(std::to_string(i + 1) + ". " + m_VersusBoard[i].p1 + " VS " + m_VersusBoard[i].p2 + ": " + std::to_string(m_VersusBoard[i].score));
		}
		break;
	}
}

void dae::LeaderboardManager::UpdateP1Text() const
{
	if (m_P1Name.empty())
		m_pP1TextComponent->GetOwner()->SetActive(false);
	else
	{
		m_pP1TextComponent->GetOwner()->SetActive(true);
		m_pP1TextComponent->SetText(m_P1Name);
	}
}

void dae::LeaderboardManager::UpdateP2Text() const
{
	if (m_P2Name.empty())
		m_pP2TextComponent->GetOwner()->SetActive(false);
	else
	{
		m_pP2TextComponent->GetOwner()->SetActive(true);
		m_pP2TextComponent->SetText(m_P2Name);
	}
}


void dae::LeaderboardManager::AppendLetter(char c)
{
	if (m_AppendToP2)
	{
		m_P2Name += c;
		UpdateP2Text();
	}
	else
	{
		m_P1Name += c;
		UpdateP1Text();
	}
}

void dae::LeaderboardManager::PopLetter()
{
	if (m_AppendToP2)
	{
		if (!m_P2Name.empty())
		{
			m_P2Name.pop_back();
			UpdateP2Text();
		}
	}
	else
	{
		if (!m_P1Name.empty())
		{
			m_P1Name.pop_back();
			UpdateP1Text();
		}
	}
}

void dae::LeaderboardManager::Enter()
{
	if (m_AppendToP2 || ServiceLocator::GetGameManager()->GetGamemode() == GameManager::GameMode::SinglePlayer)
	{
		CheckNewEntry();
		ServiceLocator::GetGameManager()->SetState(GameManager::State::LeaderBoard);
	}
	else
		m_AppendToP2 = true;
}

void dae::LeaderboardManager::LoadFromFile()
{
	std::ifstream file{ "../Data/Highscore.txt" };
	if (file.is_open())
	{
		std::stringstream lineStream;
		std::string line;
		std::string token;

		for (uint8_t i{}; i < LINES; ++i)
		{
			std::getline(file, line);
			lineStream << line;
			if (line.empty())
				continue;
			lineStream >> token;
			m_SoloBoard[i].p1 = token;
			lineStream >> token;
			m_SoloBoard[i].score = std::stoi(token);
			lineStream.str("");
			lineStream.clear();
		}

		for (uint8_t i{}; i < LINES; ++i)
		{
			std::getline(file, line);
			lineStream << line;
			if (line.empty())
				continue;
			lineStream >> token;
			m_CoopBoard[i].p1 = token;
			lineStream >> token;
			m_CoopBoard[i].p2 = token;
			lineStream >> token;
			m_CoopBoard[i].score = std::stoi(token);
			lineStream.str("");
			lineStream.clear();
		}

		for (uint8_t i{}; i < LINES; ++i)
		{
			std::getline(file, line);
			lineStream << line;
			if (line.empty())
				continue;
			lineStream >> token;
			m_VersusBoard[i].p1 = token;
			lineStream >> token;
			m_VersusBoard[i].p2 = token;
			lineStream >> token;
			m_VersusBoard[i].score = std::stoi(token);
			lineStream.str("");
			lineStream.clear();
		}

		file.close();
	}
}

void dae::LeaderboardManager::WriteToFile() const
{
	std::ofstream file{ "../Data/Highscore.txt" };
	if (file.is_open())
	{
		std::stringstream lineStream;
		std::string line;
		std::string token;

		for (uint8_t i{}; i < LINES; ++i)
			file << m_SoloBoard[i].p1 << " " << std::to_string(m_SoloBoard[i].score) << "\n";

		for (uint8_t i{}; i < LINES; ++i)
			file << m_CoopBoard[i].p1 << " " << m_CoopBoard[i].p2 << " " << std::to_string(m_CoopBoard[i].score) << "\n";

		for (uint8_t i{}; i < LINES; ++i)
			file << m_VersusBoard[i].p1 << " " << m_VersusBoard[i].p2 << " " << std::to_string(m_VersusBoard[i].score) << "\n";

		file.close();
	}
}

void dae::LeaderboardManager::CheckNewEntry()
{
	Entry e{};
	switch (ServiceLocator::GetGameManager()->GetGamemode())
	{
	case GameManager::GameMode::SinglePlayer:
		e.p1 = m_P1Name;
		e.score = ServiceLocator::GetGameManager()->GetScoreCounterComponent()->GetScore();
		m_SoloBoard.emplace_back(e);
		std::ranges::sort(m_SoloBoard, [](const Entry& a, const Entry& b) {
			return a.score > b.score;
			});
		m_SoloBoard.pop_back();
		break;

	case GameManager::GameMode::Coop:
		e.p1 = m_P1Name;
		e.p2 = m_P2Name;
		e.score = ServiceLocator::GetGameManager()->GetScoreCounterComponent()->GetScore();
		m_CoopBoard.emplace_back(e);
		std::ranges::sort(m_CoopBoard, [](const Entry& a, const Entry& b) {
			return a.score > b.score;
			});
		m_CoopBoard.pop_back();
		break;

	case GameManager::GameMode::Versus:
		e.p1 = m_P1Name;
		e.p2 = m_P2Name;
		e.score = ServiceLocator::GetGameManager()->GetScoreCounterComponent()->GetScore();
		m_VersusBoard.emplace_back(e);
		std::ranges::sort(m_VersusBoard, [](const Entry& a, const Entry& b) {
			return a.score > b.score;
			});
		m_VersusBoard.pop_back();
		break;
	}
}

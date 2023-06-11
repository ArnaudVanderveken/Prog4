#include "LeaderboardManager.h"

#include "GameObject.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

void dae::LeaderboardManager::SetP1TextComponent(TextComponent* textComponent)
{
	m_pP1TextComponent = textComponent;
}

void dae::LeaderboardManager::SetP2TextComponent(TextComponent* textComponent)
{
	m_pP2TextComponent = textComponent;
}

void dae::LeaderboardManager::SetBoardTextComponent(TextComponent* textComponent)
{
	m_pBoardTextComponent = textComponent;
}

void dae::LeaderboardManager::UpdateBoardText() const
{
	//m_pBoardTextComponent->SetText("");
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
		ServiceLocator::GetGameManager()->SetState(GameManager::State::LeaderBoard);

	else
		m_AppendToP2 = true;
}

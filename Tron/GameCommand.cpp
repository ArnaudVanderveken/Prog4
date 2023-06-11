#include "GameCommand.h"

#include "GameObject.h"
#include "InputManager.h"
#include "PlayerControllerComponent.h"
#include "ServiceLocator.h"


dae::Command::Command(GameObject* actor)
	: m_pActor(actor)
{
}

dae::GameObject* dae::Command::GetActor() const
{
	return m_pActor;
}

dae::Move::Move(GameObject* actor, Direction direction)
	: Command(actor)
	, m_Direction(direction)
{
}

void dae::Move::Execute()
{
	switch (m_Direction)
	{
	case Direction::Up:
		GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(0.f, -1.f);
		break;
	case Direction::Down:
		GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(0.f, 1.f);
		break;
	case Direction::Left:
		GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(-1.f, 0.f);
		break;
	case Direction::Right:
		GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(1.f, 0.f);
		break;
	}
}

dae::FireCommand::FireCommand(GameObject* actor, Direction direction)
	: Command(actor)
	, m_Direction(direction)
{
}

void dae::FireCommand::Execute()
{
	switch (m_Direction)
	{
	case Direction::Up:
		GetActor()->GetComponent<PlayerControllerComponent>()->Fire(0.f, -1.f);
		break;
	case Direction::Down:
		GetActor()->GetComponent<PlayerControllerComponent>()->Fire(0.f, 1.f);
		break;
	case Direction::Left:
		GetActor()->GetComponent<PlayerControllerComponent>()->Fire(-1.f, 0.f);
		break;
	case Direction::Right:
		GetActor()->GetComponent<PlayerControllerComponent>()->Fire(1.f, 0.f);
		break;
	}
}

dae::StartCommand::StartCommand() noexcept
	: Command(nullptr)
{
}

void dae::StartCommand::Execute()
{
	ServiceLocator::GetGameManager()->SetState(GameManager::State::Level1);
}

dae::PauseCommand::PauseCommand() noexcept
	: Command(nullptr)
{
}

void dae::PauseCommand::Execute()
{
	ServiceLocator::GetGameManager()->PauseGame();
}

dae::UnpauseCommand::UnpauseCommand() noexcept
	: Command(nullptr)
{
}

void dae::UnpauseCommand::Execute()
{
	ServiceLocator::GetGameManager()->UnpauseGame();
}

dae::QuitCommand::QuitCommand() noexcept
	: Command(nullptr)
{
}

void dae::QuitCommand::Execute()
{
	SDL_Event e{};
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}

dae::SkipLevelCommand::SkipLevelCommand() noexcept
	: Command(nullptr)
{
}

void dae::SkipLevelCommand::Execute()
{
	ServiceLocator::GetGameManager()->SkipLevel();
}

dae::ChangeGamemode::ChangeGamemode() noexcept
	: Command(nullptr)
{
}

void dae::ChangeGamemode::Execute()
{
	ServiceLocator::GetGameManager()->ToggleGamemode();
}

dae::MuteCommand::MuteCommand() noexcept
	: Command(nullptr)
{
}

void dae::MuteCommand::Execute()
{
	ServiceLocator::GetSoundSystem()->Mute();
}

dae::AppendLetterCommand::AppendLetterCommand(char letter) noexcept
	: Command(nullptr)
	, m_Letter(letter)
{
}

void dae::AppendLetterCommand::Execute()
{
	ServiceLocator::GetLeaderboardManager()->AppendLetter(m_Letter);
}

dae::PopLetterCommand::PopLetterCommand() noexcept
	: Command(nullptr)
{
}

void dae::PopLetterCommand::Execute()
{
	ServiceLocator::GetLeaderboardManager()->PopLetter();
}

dae::EnterCommand::EnterCommand() noexcept
	: Command(nullptr)
{
}

void dae::EnterCommand::Execute()
{
	ServiceLocator::GetLeaderboardManager()->Enter();
}

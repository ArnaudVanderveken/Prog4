#include "GameCommand.h"

#include "GameObject.h"
#include "InputManager.h"
#include "PlayerControllerComponent.h"


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

dae::DieCommand::DieCommand(GameObject* actor)
	: Command(actor)
{
}

void dae::DieCommand::Execute()
{
	GetActor()->GetComponent<PlayerControllerComponent>()->Die();
}

dae::ScoreCommand::ScoreCommand(GameObject* actor)
	: Command(actor)
{
}

void dae::ScoreCommand::Execute()
{
	GetActor()->GetComponent<PlayerControllerComponent>()->ScorePoints();
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

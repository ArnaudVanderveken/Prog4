#include "Command.h"

#include "GameObject.h"
#include "PlayerControllerComponent.h"

dae::Command::Command(GameObject* actor)
	: m_pActor(actor)
{
}

dae::GameObject* dae::Command::GetActor() const
{
	return m_pActor;
}

dae::MoveUp::MoveUp(GameObject* actor)
	: Command(actor)
{
}

void dae::MoveUp::Execute()
{
	GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(0.f, -1.f);
}

dae::MoveDown::MoveDown(GameObject* actor)
	: Command(actor)
{
}

void dae::MoveDown::Execute()
{
	GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(0.f, 1.f);
}

dae::MoveLeft::MoveLeft(GameObject* actor)
	: Command(actor)
{
}

void dae::MoveLeft::Execute()
{
	GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(-1.f, 0.f);
}

dae::MoveRight::MoveRight(GameObject* actor)
	: Command(actor)
{
}

void dae::MoveRight::Execute()
{
	GetActor()->GetComponent<PlayerControllerComponent>()->AddMovementInput(1.f, 0.f);
}

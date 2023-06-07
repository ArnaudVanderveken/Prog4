#include "PlayerControllerComponent.h"

#include "GameCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LevelComponent.h"
#include "Renderer.h"
#include "ServiceLocator.h"
#include "TimeManager.h"

dae::PlayerControllerComponent::PlayerControllerComponent(int controllerIndex, bool useKeyboard) noexcept
	: m_ControllerIndex(controllerIndex)
	, m_UseKeyboard(useKeyboard)
{
	m_PlayerIndex = GetNextPlayerIndex();
	m_DeathClipID = ServiceLocator::GetSoundSystem()->AddClip("../Data/Sounds/Shoot.mp3");
}

void dae::PlayerControllerComponent::Init()
{
	if (m_ControllerIndex != -1)
	{
		if (m_UseKeyboard)
			RegisterCombinedActions();
		else
			RegisterControllerActions();
	}
	else if (m_UseKeyboard)
		RegisterKeyboardActions();
}

void dae::PlayerControllerComponent::Update()
{
	if (abs(m_Movement.x) > 0.f || abs(m_Movement.y) > 0.f)
	{
		const auto position = GetOwner()->GetWorldTransform().position;
		glm::vec2 offset = normalize(glm::vec2{ m_Movement.x, m_Movement.y }) * m_Speed * TimeManager::GetInstance().GetElapsedTime();
		ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->QueryLevelForMovement(GetOwner()->GetLocalTransform().position, offset);
		GetOwner()->SetLocalPosition(position + glm::vec3{offset, 0});
	}
	m_Movement = glm::vec2{};
	cout << GetOwner()->GetWorldTransform().position.x << " " << GetOwner()->GetWorldTransform().position.y << endl;
}

int dae::PlayerControllerComponent::GetPlayerIndex() const
{
	return m_PlayerIndex;
}

void dae::PlayerControllerComponent::AddMovementInput(float h, float v)
{
	m_Movement.x += h;
	m_Movement.y += v;
}

void dae::PlayerControllerComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

void dae::PlayerControllerComponent::Die() const
{
	ServiceLocator::GetSoundSystem()->Play(m_DeathClipID);
	playerDied.Notify(m_PlayerIndex);
}

void dae::PlayerControllerComponent::ScorePoints() const
{
	pointsScored.Notify(m_PlayerIndex, 100);
}

int dae::PlayerControllerComponent::GetNextPlayerIndex()
{
	return s_NextAvailablePlayerIndex++;
}

void dae::PlayerControllerComponent::RegisterControllerActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, Controller::ButtonID::DPadUp, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, Controller::ButtonID::DPadDown, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, Controller::ButtonID::DPadLeft, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, Controller::ButtonID::DPadRight, m_ControllerIndex);

	InputManager::GetInstance().RegisterAction(std::make_shared<DieCommand>(GetOwner()), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonDown, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<ScoreCommand>(GetOwner()), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonRight, m_ControllerIndex);
}

void dae::PlayerControllerComponent::RegisterKeyboardActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, SDL_SCANCODE_W);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, SDL_SCANCODE_S);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, SDL_SCANCODE_A);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, SDL_SCANCODE_D);

	InputManager::GetInstance().RegisterAction(std::make_shared<DieCommand>(GetOwner()), InputAction::ActionType::Down, SDL_SCANCODE_Q);
	InputManager::GetInstance().RegisterAction(std::make_shared<ScoreCommand>(GetOwner()), InputAction::ActionType::Down, SDL_SCANCODE_E);
}

void dae::PlayerControllerComponent::RegisterCombinedActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, Controller::ButtonID::DPadUp, m_ControllerIndex, SDL_SCANCODE_W);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, Controller::ButtonID::DPadDown, m_ControllerIndex, SDL_SCANCODE_S);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, Controller::ButtonID::DPadLeft, m_ControllerIndex, SDL_SCANCODE_A);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, Controller::ButtonID::DPadRight, m_ControllerIndex, SDL_SCANCODE_D);

	InputManager::GetInstance().RegisterAction(std::make_shared<DieCommand>(GetOwner()), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonDown, m_ControllerIndex, SDL_SCANCODE_Q);
	InputManager::GetInstance().RegisterAction(std::make_shared<ScoreCommand>(GetOwner()), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonRight, m_ControllerIndex, SDL_SCANCODE_E);
}
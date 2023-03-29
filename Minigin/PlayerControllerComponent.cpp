#include "PlayerControllerComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "Time.h"

dae::PlayerControllerComponent::PlayerControllerComponent(int controllerIndex, bool useKeyboard) noexcept
	: m_ControllerIndex(controllerIndex)
	, m_UseKeyboard(useKeyboard)
{
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
		const auto position = GetOwner()->GetLocalTransform().position;
		const glm::vec3 offset = normalize(glm::vec3{ m_Movement.x, m_Movement.y, 0 }) * m_Speed * Time::GetInstance().GetElapsedTime();
		GetOwner()->SetLocalPosition(position + offset);
	}
	m_Movement = glm::vec2{};
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

void dae::PlayerControllerComponent::Die()
{
}

void dae::PlayerControllerComponent::ScorePoints()
{
}

void dae::PlayerControllerComponent::RegisterControllerActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, Controller::ButtonID::DPadUp, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, Controller::ButtonID::DPadDown, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, Controller::ButtonID::DPadLeft, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, Controller::ButtonID::DPadRight, m_ControllerIndex);
}

void dae::PlayerControllerComponent::RegisterKeyboardActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, SDL_SCANCODE_W);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, SDL_SCANCODE_S);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, SDL_SCANCODE_A);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, SDL_SCANCODE_D);
}

void dae::PlayerControllerComponent::RegisterCombinedActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, Controller::ButtonID::DPadUp, m_ControllerIndex, SDL_SCANCODE_W);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, Controller::ButtonID::DPadDown, m_ControllerIndex, SDL_SCANCODE_S);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, Controller::ButtonID::DPadLeft, m_ControllerIndex, SDL_SCANCODE_A);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, Controller::ButtonID::DPadRight, m_ControllerIndex, SDL_SCANCODE_D);
}
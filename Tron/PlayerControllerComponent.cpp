#include "PlayerControllerComponent.h"

#include "GameCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LevelComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ServiceLocator.h"
#include "TimeManager.h"

dae::PlayerControllerComponent::PlayerControllerComponent(int controllerIndex, bool useKeyboard, RenderComponent* bodyRenderComponent, RenderComponent* gunRenderComponent) noexcept
	: m_ControllerIndex(controllerIndex)
	, m_UseKeyboard(useKeyboard)
	, m_pBodyRenderComponent(bodyRenderComponent)
	, m_pGunRenderComponent(gunRenderComponent)
{
	m_PlayerIndex = GetNextPlayerIndex();
	m_DeathClipID = ServiceLocator::GetSoundSystem()->AddClip("../Data/Sounds/Shoot.mp3");
}

void dae::PlayerControllerComponent::Init()
{
	BindActions();
}

void dae::PlayerControllerComponent::Update()
{
	// MOVEMENT
	if (abs(m_Movement.x) > 0.f || abs(m_Movement.y) > 0.f)
	{
		const auto position = GetOwner()->GetWorldTransform().position;
		glm::vec2 offset = normalize(glm::vec2{ m_Movement.x, m_Movement.y }) * m_Speed * TimeManager::GetInstance().GetElapsedTime();
		ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->QueryLevelForMovement(GetOwner()->GetLocalTransform().position, offset);
		GetOwner()->SetLocalPosition(position + glm::vec3{offset, 0});

		if (m_pBodyRenderComponent)
		{
			if (abs(m_Movement.x) > abs(m_Movement.y))
			{
				if (m_Movement.x >= 0.0f)
					m_pBodyRenderComponent->SetAngle(0.0f);
				else
					m_pBodyRenderComponent->SetAngle(180.0f);
			}
			else
			{
				if (m_Movement.y >= 0.0f)
					m_pBodyRenderComponent->SetAngle(90.0f);
				else
					m_pBodyRenderComponent->SetAngle(270.0f);
			}
		}
	}

	// FIRE BULLET
	m_Cooldown += TimeManager::GetInstance().GetElapsedTime();
	if (abs(m_FireInput.x) > 0.f || abs(m_FireInput.y) > 0.f)
	{
		if (m_Cooldown >= FIRE_COOLDOWN)
		{
			const auto type = static_cast<BulletComponent::Type>(m_PlayerIndex + 1);
			const glm::vec2 direction = normalize(glm::vec2{ m_FireInput.x, m_FireInput.y });
			ServiceLocator::GetBulletManager()->SpawnBullet(GetOwner()->GetWorldTransform().position, type, direction);
			m_Cooldown = 0.0f;
		}

		if (m_pGunRenderComponent)
		{
			const auto normalized = normalize(glm::vec2{ m_FireInput.x, m_FireInput.y });
			const float angle = glm::degrees(glm::atan(normalized.y, normalized.x));
			m_pGunRenderComponent->SetAngle(angle);
		}
	}

	// RESET
	m_Movement = glm::vec2{};
	m_FireInput = glm::vec2{};
}

int dae::PlayerControllerComponent::GetPlayerIndex() const
{
	return m_PlayerIndex;
}

void dae::PlayerControllerComponent::BindActions() const
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

void dae::PlayerControllerComponent::Fire(float h, float v)
{
	m_FireInput.x += h;
	m_FireInput.y += v;
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

	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Up), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonUp, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Down), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonDown, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Left), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonLeft, m_ControllerIndex);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Right), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonRight, m_ControllerIndex);
}

void dae::PlayerControllerComponent::RegisterKeyboardActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, SDL_SCANCODE_W);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, SDL_SCANCODE_S);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, SDL_SCANCODE_A);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, SDL_SCANCODE_D);

	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Up), InputAction::ActionType::Down, SDL_SCANCODE_UP);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Down), InputAction::ActionType::Down, SDL_SCANCODE_DOWN);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Left), InputAction::ActionType::Down, SDL_SCANCODE_LEFT);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Right), InputAction::ActionType::Down, SDL_SCANCODE_RIGHT);
}

void dae::PlayerControllerComponent::RegisterCombinedActions() const
{
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Up), InputAction::ActionType::Pressed, Controller::ButtonID::DPadUp, m_ControllerIndex, SDL_SCANCODE_W);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Down), InputAction::ActionType::Pressed, Controller::ButtonID::DPadDown, m_ControllerIndex, SDL_SCANCODE_S);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Left), InputAction::ActionType::Pressed, Controller::ButtonID::DPadLeft, m_ControllerIndex, SDL_SCANCODE_A);
	InputManager::GetInstance().RegisterAction(std::make_shared<Move>(GetOwner(), Move::Direction::Right), InputAction::ActionType::Pressed, Controller::ButtonID::DPadRight, m_ControllerIndex, SDL_SCANCODE_D);
	
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Up), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonUp, m_ControllerIndex, SDL_SCANCODE_UP);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Down), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonDown, m_ControllerIndex, SDL_SCANCODE_DOWN);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Left), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonLeft, m_ControllerIndex, SDL_SCANCODE_LEFT);
	InputManager::GetInstance().RegisterAction(std::make_shared<FireCommand>(GetOwner(), FireCommand::Direction::Right), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonRight, m_ControllerIndex, SDL_SCANCODE_RIGHT);
}
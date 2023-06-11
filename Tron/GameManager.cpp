#include "GameManager.h"

#include "GameCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LevelComponent.h"
#include "LifeTrackerComponent.h"
#include "PlayerControllerComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreTrackerComponent.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

dae::GameManager::GameManager() noexcept
{
	// Sounds
	m_MainMenuSound = ServiceLocator::GetSoundSystem()->AddClip("../Data/Sounds/MainMenuMusic.mp3");
	m_BackgroundSound = ServiceLocator::GetSoundSystem()->AddClip("../Data/Sounds/Background.mp3");
	m_FailSound = ServiceLocator::GetSoundSystem()->AddClip("../Data/Sounds/FailMusic.mp3");

	// Fonts
	const auto lingua12 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	const auto lingua36 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// Red Tank (P1)
	m_pP1Tank = std::make_shared<GameObject>(false);
	auto body = new RenderComponent("Sprites/RedTank.png", { 0.5f, 0.5f });
	m_pP1Tank->AddComponent(body);
	auto gun = new RenderComponent("Sprites/RedTankGun.png", { 0.5f, 0.5f });
	m_pP1Tank->AddComponent(gun);
	m_pP1Component = new PlayerControllerComponent(-1, true, body, gun);
	m_pP1Tank->AddComponent(m_pP1Component);

	// Green Tank (P2)
	m_pP2Tank = std::make_shared<GameObject>(false);
	body = new RenderComponent("Sprites/GreenTank.png", { 0.5f, 0.5f });
	m_pP2Tank->AddComponent(body);
	body = new RenderComponent("Sprites/GreenTankGun.png", { 0.5f, 0.5f });
	m_pP2Tank->AddComponent(body);
	m_pP2Component = new PlayerControllerComponent(0, false, body, gun);
	m_pP2Tank->AddComponent(m_pP2Component);

	// Enemy tanks
	for (uint8_t i{}; i < ENEMY_PRELOAD; ++i)
	{
		m_pEnemyTanks[i] = std::make_shared<GameObject>(false);
		body = new RenderComponent("Sprites/BlueTank.png", { 0.5f, 0.5f });
		m_pEnemyTanks[i]->AddComponent(body);
		gun = new RenderComponent("Sprites/BlueTankGun.png", { 0.5f, 0.5f });
		m_pEnemyTanks[i]->AddComponent(gun);
		//m_pP1Tank->AddComponent(new PlayerControllerComponent(-1, true, body, gun));
	}

	// Recognizers tanks
	for (uint8_t i{}; i < ENEMY_PRELOAD; ++i)
	{
		m_pRecognizerTanks[i] = std::make_shared<GameObject>(false);
		body = new RenderComponent("Sprites/BlueTank.png", { 0.5f, 0.5f });
		m_pRecognizerTanks[i]->AddComponent(body);
		gun = new RenderComponent("Sprites/BlueTankGun.png", { 0.5f, 0.5f });
		m_pRecognizerTanks[i]->AddComponent(gun);
		//m_pP1Tank->AddComponent(new PlayerControllerComponent(-1, true, body, gun));
	}

	// Life tracker
	m_pLifeCounter = std::make_shared<GameObject>(false);
	m_pLifeCounter->AddComponent(new RenderComponent(""));
	m_pLifeCounter->AddComponent(new TextComponent("DefaultText...", SDL_Color(255, 255, 255), lingua12));
	m_pLifeCounter->AddComponent(new LifeTrackerComponent());
	m_pLifeCounter->SetLocalPosition({ 5, 100, 0 });

	// Score tracker
	m_pScoreCounter = std::make_shared<GameObject>(false);
	m_pScoreCounter->AddComponent(new RenderComponent(""));
	m_pScoreCounter->AddComponent(new TextComponent("DefaultText...", SDL_Color(255, 255, 255), lingua12));
	m_pScoreCounter->AddComponent(new ScoreTrackerComponent());
	m_pScoreCounter->SetLocalPosition({ 5, 120, 0 });

	// Bind Main menu commands
	SetState(State::MainMenu, true);
}

void dae::GameManager::ToggleGamemode()
{
	m_Gamemode = static_cast<GameMode>((static_cast<int>(m_Gamemode) + 1) % static_cast<int>(GameMode::SIZE));
	UpdateGamemodeText();
}

void dae::GameManager::PauseGame()
{
	m_PrePauseState = m_State;
	SetState(State::PauseMenu);
}

void dae::GameManager::UnpauseGame()
{
	SetState(m_PrePauseState);
}

void dae::GameManager::SkipLevel()
{
	switch (m_State)
	{
	case State::Level1:
		SetState(State::Level2);
		break;

	case State::Level2:
		SetState(State::Level3);
		break;

	case State::Level3:
		SetState(State::Level1);
		break;

	default:
		break;
	}
}

void dae::GameManager::SetState(State state, bool skipExit)
{
	if (!skipExit)
		OnStateExit();
	m_State = state;
	OnStateEnter();
}

void dae::GameManager::ResetTanks() const
{
	// P1
	const auto& p1Start{ ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->GetPlayer1Start() };
	m_pP1Tank->SetLocalPosition({ p1Start.x, p1Start.y, 0.0f });
	m_pP1Tank->SetActive(true);

	// P2
	const auto& p2Start{ ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->GetPlayer1Start() };
	m_pP2Tank->SetLocalPosition({ p2Start.x, p2Start.y, 0.0f });
	if (m_Gamemode == GameMode::Coop)
		m_pP2Tank->SetActive(true);

	// Enemies
	const auto& pEnemiesStarts{ ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->GetNormalEnemiesStarts() };
	size_t i{};
	for (; i < pEnemiesStarts.size(); ++i)
	{
		const auto& enemyStart{ pEnemiesStarts[i] };
		m_pEnemyTanks[i]->SetLocalPosition({ enemyStart.x, enemyStart.y, 0.0f });
		m_pEnemyTanks[i]->SetActive(true);
	}
	for (; i < ENEMY_PRELOAD; ++i)
		m_pEnemyTanks[i]->SetActive(false);

	// Recognizers
	const auto& pRecognizersStarts{ ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->GetRecognizersStarts() };
	i = 0;
	for (; i < pRecognizersStarts.size(); ++i)
	{
		const auto& enemyStart{ pRecognizersStarts[i] };
		m_pRecognizerTanks[i]->SetLocalPosition({ enemyStart.x, enemyStart.y, 0.0f });
		m_pRecognizerTanks[i]->SetActive(true);
	}
	for (; i < ENEMY_PRELOAD; ++i)
		m_pRecognizerTanks[i]->SetActive(false);
}

void dae::GameManager::RegisterGamemodeText(TextComponent* pTextComponent)
{
	m_pGamemodeText = pTextComponent;
	UpdateGamemodeText();
}

const std::shared_ptr<dae::GameObject>& dae::GameManager::GetP1Tank() const
{
	return m_pP1Tank;
}

const std::shared_ptr<dae::GameObject>& dae::GameManager::GetP2Tank() const
{
	return m_pP2Tank;
}

const std::array<std::shared_ptr<dae::GameObject>, dae::GameManager::ENEMY_PRELOAD>& dae::GameManager::GetEnemyTanks() const
{
	return m_pEnemyTanks;
}

const std::array<std::shared_ptr<dae::GameObject>, dae::GameManager::ENEMY_PRELOAD>& dae::GameManager::GetRecognizerTanks() const
{
	return m_pRecognizerTanks;
}

const std::shared_ptr<dae::GameObject>& dae::GameManager::GetLifeCounter() const
{
	return m_pLifeCounter;
}

const std::shared_ptr<dae::GameObject>& dae::GameManager::GetScoreCounter() const
{
	return m_pScoreCounter;
}

void dae::GameManager::OnStateEnter()
{
	switch (m_State)
	{
	case State::MainMenu:
		BindMainMenuCommands();
		SceneManager::GetInstance().SetActiveScene(0);
		ServiceLocator::GetSoundSystem()->Play(m_MainMenuSound);
		break;

	case State::Level1:
		BindLevelCommands();
		SceneManager::GetInstance().SetActiveScene(1);
		ServiceLocator::GetLevelManager()->LoadLevel(0);
		if (!m_ResetLevel)
			m_ResetLevel = true;
		else
		{
			ResetTanks();
			ServiceLocator::GetBulletManager()->ResetBullets();
		}
		break;

	case State::Level2:
		BindLevelCommands();
		SceneManager::GetInstance().SetActiveScene(2);
		ServiceLocator::GetLevelManager()->LoadLevel(1);
		if (!m_ResetLevel)
			m_ResetLevel = true;
		else
		{
			ResetTanks();
			ServiceLocator::GetBulletManager()->ResetBullets();
		}
		break;

	case State::Level3:
		BindLevelCommands();
		SceneManager::GetInstance().SetActiveScene(3);
		ServiceLocator::GetLevelManager()->LoadLevel(2);
		if (!m_ResetLevel)
			m_ResetLevel = true;
		else
		{
			ResetTanks();
			ServiceLocator::GetBulletManager()->ResetBullets();
		}
		break;

	case State::PauseMenu:
		BindPauseCommands();
		SceneManager::GetInstance().SetActiveScene(4);
		m_ResetLevel = false;
		break;

	case State::EndScreen:
		ServiceLocator::GetSoundSystem()->Stop(m_BackgroundSound);
		ServiceLocator::GetSoundSystem()->Play(m_FailSound);
		BindEndScreenCommands();
		SceneManager::GetInstance().SetActiveScene(5);
		break;

	case State::LeaderBoard:
		BindLeaderBoardCommands();
		SceneManager::GetInstance().SetActiveScene(6);
		break;
	}
}

void dae::GameManager::OnStateExit()
{
	switch (m_State)
	{
	case State::MainMenu:
		ServiceLocator::GetSoundSystem()->Stop(m_MainMenuSound);
		ServiceLocator::GetSoundSystem()->Play(m_BackgroundSound, true);
		InputManager::GetInstance().ClearActions();
		break;

	case State::Level1:
		ServiceLocator::GetLevelManager()->UnloadLevel(0);
		InputManager::GetInstance().ClearActions();
		break;

	case State::Level2:
		ServiceLocator::GetLevelManager()->UnloadLevel(1);
		InputManager::GetInstance().ClearActions();
		break;

	case State::Level3:
		ServiceLocator::GetLevelManager()->UnloadLevel(2);
		InputManager::GetInstance().ClearActions();
		break;

	case State::PauseMenu:
		InputManager::GetInstance().ClearActions();
		break;

	case State::EndScreen:
		InputManager::GetInstance().ClearActions();
		break;

	case State::LeaderBoard:
		InputManager::GetInstance().ClearActions();
		break;
	}
}

void dae::GameManager::BindMainMenuCommands()
{
	InputManager::GetInstance().RegisterAction(std::make_shared<StartCommand>(), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonDown, 0, SDL_SCANCODE_SPACE);
	InputManager::GetInstance().RegisterAction(std::make_shared<QuitCommand>(), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonRight, 0, SDL_SCANCODE_ESCAPE);
	InputManager::GetInstance().RegisterAction(std::make_shared<ChangeGamemode>(), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonLeft, 0, SDL_SCANCODE_TAB);
}

void dae::GameManager::BindLevelCommands()
{
	InputManager::GetInstance().RegisterAction(std::make_shared<PauseCommand>(), InputAction::ActionType::Down, Controller::ButtonID::Start, 0, SDL_SCANCODE_TAB);
	InputManager::GetInstance().RegisterAction(std::make_shared<SkipLevelCommand>(), InputAction::ActionType::Down, Controller::ButtonID::Back, 0, SDL_SCANCODE_F1);
	m_pP1Component->BindActions();
	if (m_Gamemode != GameMode::SinglePlayer)
		m_pP2Component->BindActions();
}

void dae::GameManager::BindPauseCommands()
{
	InputManager::GetInstance().RegisterAction(std::make_shared<UnpauseCommand>(), InputAction::ActionType::Down, Controller::ButtonID::Start, 0, SDL_SCANCODE_TAB);
	InputManager::GetInstance().RegisterAction(std::make_shared<QuitCommand>(), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonRight, 0, SDL_SCANCODE_ESCAPE);
}

void dae::GameManager::BindEndScreenCommands()
{
	InputManager::GetInstance().RegisterAction(std::make_shared<StartCommand>(), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonDown, 0, SDL_SCANCODE_SPACE);
	InputManager::GetInstance().RegisterAction(std::make_shared<QuitCommand>(), InputAction::ActionType::Down, Controller::ButtonID::FaceButtonRight, 0, SDL_SCANCODE_ESCAPE);
}

void dae::GameManager::BindLeaderBoardCommands()
{
}

void dae::GameManager::UpdateGamemodeText()
{
	switch (m_Gamemode)
	{
	case GameMode::SinglePlayer:
		m_pGamemodeText->SetText("Single Player");
		break;

	case GameMode::Coop:
		m_pGamemodeText->SetText("Co-op");
		break;

	case GameMode::Versus:
		m_pGamemodeText->SetText("Versus");
		break;

	default:
		break;
	}
}

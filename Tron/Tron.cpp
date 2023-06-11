#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <memory>

#include "Minigin.h"

#include "FPSCounterComponent.h"
#include "GameObject.h"
#include "GameManager.h"
#include "LevelComponent.h"
#include "LevelManager.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "TextComponent.h"


void load()
{
	using namespace dae;

	// Scenes
	auto& mainMenu = SceneManager::GetInstance().CreateScene("MainMenu");
	auto& level1 = SceneManager::GetInstance().CreateScene("Level1");
	auto& level2 = SceneManager::GetInstance().CreateScene("Level2");
	auto& level3 = SceneManager::GetInstance().CreateScene("Level3");
	auto& pauseMenu = SceneManager::GetInstance().CreateScene("PauseMenu");
	auto& endScreen = SceneManager::GetInstance().CreateScene("EndScreen");
	auto& leaderboard = SceneManager::GetInstance().CreateScene("Leaderboard");

	// Register services
	ServiceLocator::RegisterSoundSystem(std::make_shared<SoundSystem>());
	ServiceLocator::RegisterLevelManager(std::make_shared<LevelManager>());
	ServiceLocator::RegisterBulletManager(std::make_shared<BulletManager>());
	ServiceLocator::RegisterGameManager(std::make_shared<GameManager>());

	// Fonts
	const auto Lingua12 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	const auto Lingua24 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	const auto Lingua36 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// FPS counter
	const auto pFPSCounter = std::make_shared<GameObject>();
	pFPSCounter->AddComponent(new RenderComponent(""));
	pFPSCounter->AddComponent(new TextComponent("DefaultText...", SDL_Color(0, 255, 0), Lingua12));
	pFPSCounter->AddComponent(new FPSCounterComponent());
	pFPSCounter->SetLocalPosition({ 5, 5, 0 });
	level1.Add(pFPSCounter);
	level2.Add(pFPSCounter);
	level3.Add(pFPSCounter);

	// Levels
	level1.Add(ServiceLocator::GetLevelManager()->GetLevelObject(0));
	level2.Add(ServiceLocator::GetLevelManager()->GetLevelObject(1));
	level3.Add(ServiceLocator::GetLevelManager()->GetLevelObject(2));

	// Red Tank
	const auto& pRedTank = ServiceLocator::GetGameManager()->GetP1Tank();
	level1.Add(pRedTank);
	level2.Add(pRedTank);
	level3.Add(pRedTank);

	// Blue Tank
	const auto& pGreenTank = ServiceLocator::GetGameManager()->GetP2Tank();
	level1.Add(pGreenTank);
	level2.Add(pGreenTank);
	level3.Add(pGreenTank);

	// Enemy Tanks
	const auto& pEnemyTanks = ServiceLocator::GetGameManager()->GetEnemyTanks();
	for (const auto& pTank : pEnemyTanks)
	{
		level1.Add(pTank);
		level2.Add(pTank);
		level3.Add(pTank);
	}

	// Recognizer Tanks
	const auto& pRecognizers = ServiceLocator::GetGameManager()->GetRecognizerTanks();
	for (const auto& pTank : pRecognizers)
	{
		level1.Add(pTank);
		level2.Add(pTank);
		level3.Add(pTank);
	}

	// Bullets
	const auto& pBullets = ServiceLocator::GetBulletManager()->GetBullets();
	for (const auto& pBullet : pBullets)
	{
		level1.Add(pBullet);
		level2.Add(pBullet);
		level3.Add(pBullet);
	}

	// RT Life counter
	const auto pLifeCounter = ServiceLocator::GetGameManager()->GetLifeCounter();
	level1.Add(pLifeCounter);
	level2.Add(pLifeCounter);
	level3.Add(pLifeCounter);

	// RT Score counter
	const auto pScoreCounter = ServiceLocator::GetGameManager()->GetScoreCounter();
	level1.Add(pScoreCounter);
	level2.Add(pScoreCounter);
	level3.Add(pScoreCounter);

	// Tab to pause text
	const auto pPauseText = std::make_shared<GameObject>();
	pPauseText->AddComponent(new RenderComponent(""));
	pPauseText->AddComponent(new TextComponent("Start/Tab to pause", SDL_Color(255, 255, 255), Lingua24));
	pPauseText->SetLocalPosition({ 200, 440, 0 });
	level1.Add(pPauseText);
	level2.Add(pPauseText);
	level3.Add(pPauseText);

	// Main menu texts
	auto mainMenuText = std::make_shared<GameObject>();
	mainMenuText->AddComponent(new RenderComponent(""));
	mainMenuText->AddComponent(new TextComponent("A/Space to start", SDL_Color(0, 255, 0), Lingua36));
	mainMenuText->SetLocalPosition({ 180, 20, 0 });
	mainMenu.Add(mainMenuText);

	mainMenuText = std::make_shared<GameObject>();
	mainMenuText->AddComponent(new RenderComponent(""));
	mainMenuText->AddComponent(new TextComponent("B/Escape to quit", SDL_Color(255, 0, 0), Lingua36));
	mainMenuText->SetLocalPosition({ 180, 80, 0 });
	mainMenu.Add(mainMenuText);

	mainMenuText = std::make_shared<GameObject>();
	mainMenuText->AddComponent(new RenderComponent(""));
	mainMenuText->AddComponent(new TextComponent("X/Tab to change gamemode", SDL_Color(255, 255, 0), Lingua36));
	mainMenuText->SetLocalPosition({ 100, 140, 0 });
	mainMenu.Add(mainMenuText);

	mainMenuText = std::make_shared<GameObject>();
	mainMenuText->AddComponent(new RenderComponent(""));
	const auto pText = new TextComponent("Single player", SDL_Color(255, 255, 255), Lingua24);
	mainMenuText->AddComponent(pText);
	ServiceLocator::GetGameManager()->RegisterGamemodeText(pText);
	mainMenuText->SetLocalPosition({ 260, 180, 0 });
	mainMenu.Add(mainMenuText);

	// Pause menu texts
	auto pauseMenuText = std::make_shared<GameObject>();
	pauseMenuText->AddComponent(new RenderComponent(""));
	pauseMenuText->AddComponent(new TextComponent("Start/Tab to resume", SDL_Color(0, 255, 0), Lingua36));
	pauseMenuText->SetLocalPosition({ 180, 20, 0 });
	pauseMenu.Add(pauseMenuText);

	pauseMenuText = std::make_shared<GameObject>();
	pauseMenuText->AddComponent(new RenderComponent(""));
	pauseMenuText->AddComponent(new TextComponent("B/Escape to quit", SDL_Color(255, 0, 0), Lingua36));
	pauseMenuText->SetLocalPosition({ 180, 80, 0 });
	pauseMenu.Add(pauseMenuText);

	// End screen texts
	auto endScreenText = std::make_shared<GameObject>();
	endScreenText->AddComponent(new RenderComponent(""));
	endScreenText->AddComponent(new TextComponent("GAME OVER", SDL_Color(255, 0, 0), Lingua36));
	endScreenText->SetLocalPosition({ 180, 20, 0 });
	endScreen.Add(endScreenText);

	// Leaderboard texts
	auto leaderboardText = std::make_shared<GameObject>();
	leaderboardText->AddComponent(new RenderComponent(""));
	leaderboardText->AddComponent(new TextComponent("LEADERBOARD", SDL_Color(255, 255, 0), Lingua36));
	leaderboardText->SetLocalPosition({ 180, 20, 0 });
	leaderboard.Add(leaderboardText);

	// display controls on the console
	std::cout << "Controls:"
				"\n\tController:"
				"\n\t\tMove: DPAD"
				"\n\t\tDie: A"
				"\n\t\tScore: B"
				"\n\tKeyboard:"
				"\n\t\tMove: WASD"
				"\n\t\tDie (+test sound): Q"
				"\n\t\tScore: E"
				"\n"
				"\nPlayer 1: Keyboard"
				"\nPlayer 2: Controller" << std::endl;
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
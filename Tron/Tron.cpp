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

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "FPSCounterComponent.h"
#include "GameObject.h"
#include "LifeTrackerComponent.h" 
#include "RenderComponent.h"
#include "ScoreTrackerComponent.h"
#include "TextComponent.h"
#include "PlayerControllerComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent("background.tga"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent("logo.tga"));
	go->SetLocalPosition({ 216, 180, 0 });
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(""));
	go->AddComponent(new dae::TextComponent("Programming 4 Assignment", SDL_Color(255, 255, 255), font));
	go->SetLocalPosition({ 80, 20, 0 });
	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(""));
	go->AddComponent(new dae::TextComponent("DefaultText...", SDL_Color(0, 255, 0), font));
	go->AddComponent(new dae::FPSCounterComponent());
	go->SetLocalPosition({ 5, 5, 0 });
	scene.Add(go);

	// Red Tank
	const auto redTank = std::make_shared<dae::GameObject>();
	redTank->AddComponent(new dae::RenderComponent("RedTank.png"));
	redTank->AddComponent(new dae::PlayerControllerComponent(-1, true));
	redTank->SetLocalPosition({ 200, 300, 0 });
	scene.Add(redTank);

	// Blue Tank
	const auto blueTank = std::make_shared<dae::GameObject>();
	blueTank->AddComponent(new dae::RenderComponent("BlueTank.png"));
	blueTank->AddComponent(new dae::PlayerControllerComponent(0, false));
	if (auto component = blueTank->GetComponent<dae::PlayerControllerComponent>())
		component->SetSpeed(100.f);
	blueTank->SetLocalPosition({ 400, 300, 0 });
	scene.Add(blueTank);

	// RT Life counter
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(""));
	go->AddComponent(new dae::TextComponent("DefaultText...", SDL_Color(0, 255, 0), font));
	auto playerControllerComponent = redTank->GetComponent<dae::PlayerControllerComponent>();
	go->AddComponent(new dae::LifeTrackerComponent(playerControllerComponent->GetPlayerIndex()));
	playerControllerComponent->AddObserver(go->GetComponent<dae::LifeTrackerComponent>());
	go->SetLocalPosition({ 5, 300, 0 });
	scene.Add(go);

	// RT Score counter
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(""));
	go->AddComponent(new dae::TextComponent("DefaultText...", SDL_Color(0, 255, 0), font));
	go->AddComponent(new dae::ScoreTrackerComponent(playerControllerComponent->GetPlayerIndex()));
	playerControllerComponent->AddObserver(go->GetComponent<dae::ScoreTrackerComponent>());
	go->SetLocalPosition({ 5, 320, 0 });
	scene.Add(go);

	// BT Life counter
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(""));
	go->AddComponent(new dae::TextComponent("DefaultText...", SDL_Color(0, 255, 0), font));
	playerControllerComponent = blueTank->GetComponent<dae::PlayerControllerComponent>();
	go->AddComponent(new dae::LifeTrackerComponent(playerControllerComponent->GetPlayerIndex()));
	playerControllerComponent->AddObserver(go->GetComponent<dae::LifeTrackerComponent>());
	go->SetLocalPosition({ 5, 400, 0 });
	scene.Add(go);

	// BT Score counter
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(""));
	go->AddComponent(new dae::TextComponent("DefaultText...", SDL_Color(0, 255, 0), font));
	go->AddComponent(new dae::ScoreTrackerComponent(playerControllerComponent->GetPlayerIndex()));
	playerControllerComponent->AddObserver(go->GetComponent<dae::ScoreTrackerComponent>());
	go->SetLocalPosition({ 5, 420, 0 });
	scene.Add(go);

	// display controls on the console
	std::cout << "Controls:\n\tController:\n\t\tMove: DPAD\n\t\tDie: A\n\t\tScore: B\n\tKeyboard:\n\t\tMove: WASD\n\t\tDie: Q\n\t\tScore: E\n\nPlayer 1: Keyboard\nPlayer 2: Controller" << std::endl;
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
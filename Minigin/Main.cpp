#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "ParentingTestComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent("background.tga", go.get()));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent("logo.tga", go.get()));
	go->SetLocalPosition({ 216, 180, 0 });
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent("", go.get()));
	go->AddComponent(new dae::TextComponent("Programming 4 Assignment", SDL_Color(255, 255, 255), font, go.get()));
	go->SetLocalPosition({ 80, 20, 0 });
	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent("", go.get()));
	go->AddComponent(new dae::TextComponent("fgebrnfmkgvbi", SDL_Color(0, 255, 0), font, go.get()));
	go->AddComponent(new dae::FPSCounterComponent(go.get()));
	go->SetLocalPosition({ 5, 5, 0 });
	scene.Add(go);

	// Red Tank
	auto redTank = std::make_shared<dae::GameObject>();
	redTank->AddComponent(new dae::RenderComponent("RedTank.png", redTank.get()));
	redTank->AddComponent(new dae::ParentingTestComponent(redTank.get()));
	redTank->SetLocalPosition({ 300, 300, 0 });
	scene.Add(redTank);

	// Blue Tank
	auto blueTank = std::make_shared<dae::GameObject>();
	blueTank->AddComponent(new dae::RenderComponent("BlueTank.png", blueTank.get()));
	blueTank->SetLocalPosition({ 0, -50, 0 });
	blueTank->SetParent(redTank.get(), false);
	scene.Add(blueTank);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
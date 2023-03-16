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
	go->AddComponent(new dae::TextComponent("fgebrnfmkgvbi", SDL_Color(0, 255, 0), font));
	go->AddComponent(new dae::FPSCounterComponent());
	go->SetLocalPosition({ 5, 5, 0 });
	scene.Add(go);

	// Root object for parenting test
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition({ 300, 300, 0 });
	scene.Add(go);

	// Red Tank
	const auto redTank = std::make_shared<dae::GameObject>();
	redTank->AddComponent(new dae::RenderComponent("RedTank.png"));
	redTank->AddComponent(new dae::ParentingTestComponent());
	redTank->SetParent(go.get(), false);
	scene.Add(redTank);

	// Blue Tank
	const auto blueTank = std::make_shared<dae::GameObject>();
	blueTank->AddComponent(new dae::RenderComponent("BlueTank.png"));
	blueTank->AddComponent(new dae::ParentingTestComponent());
	if (dae::ParentingTestComponent* test = blueTank->GetComponent<dae::ParentingTestComponent>())
		test->SetDirection(-1);
	blueTank->SetParent(redTank.get(), false);
	scene.Add(blueTank);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
#pragma once
#include <memory>

#include "BulletManager.h"
#include "GameManager.h"
#include "LevelManager.h"
#include "SoundSystem.h"

class ServiceLocator final
{
public:
	ServiceLocator() noexcept = default;
	~ServiceLocator() = default;

	ServiceLocator(const ServiceLocator& other) noexcept = delete;
	ServiceLocator& operator=(const ServiceLocator& other) noexcept = delete;
	ServiceLocator(ServiceLocator&& other) noexcept = delete;
	ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;
	
	static void RegisterSoundSystem(const std::shared_ptr<SoundSystem>& soundSystem);
	[[nodiscard]] static SoundSystem* GetSoundSystem();

	static void RegisterLevelManager(const std::shared_ptr<dae::LevelManager>& levelManager);
	[[nodiscard]] static dae::LevelManager* GetLevelManager();

	static void RegisterBulletManager(const std::shared_ptr<dae::BulletManager>& bulletManager);
	[[nodiscard]] static dae::BulletManager* GetBulletManager();

	static void RegisterGameManager(const std::shared_ptr<dae::GameManager>& gameManager);
	[[nodiscard]] static dae::GameManager* GetGameManager();

private:
	inline static std::shared_ptr<SoundSystem> m_pSoundSystem{};
	inline static std::unique_ptr<SoundSystem> m_pDefaultSoundSystem{ std::make_unique<NULL_SoundSystem>() };
	inline static std::shared_ptr<dae::LevelManager> m_pLevelManager{};
	inline static std::shared_ptr<dae::BulletManager> m_pBulletManager{};
	inline static std::shared_ptr<dae::GameManager> m_pGameManager{};
};


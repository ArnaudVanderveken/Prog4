#pragma once
#include <memory>

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
	
	static void RegisterSoundSystem(std::shared_ptr<SoundSystem> soundSystem);
	static SoundSystem* GetSoundSystem();

private:
	inline static std::shared_ptr<SoundSystem> m_pSoundSystem{};
	inline static std::unique_ptr<SoundSystem> m_pDefaultSoundSystem{ std::make_unique<NULL_SoundSystem>() };
};


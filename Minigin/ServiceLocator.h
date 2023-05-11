#pragma once
#include <memory>

#include "SoundSystem.h"

class ServiceLocator final
{
public:
	static void RegisterSoundSystem(SoundSystem* soundSystem);
	static SoundSystem* GetSoundSystem();

private:
	inline static SoundSystem* m_pSoundSystem{};
	inline static std::unique_ptr<SoundSystem> m_pDefaultSoundSystem{};
};


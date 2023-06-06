#include "ServiceLocator.h"

#include <utility>


void ServiceLocator::RegisterSoundSystem(std::shared_ptr<SoundSystem> soundSystem)
{
		m_pSoundSystem = std::move(soundSystem);
}

SoundSystem* ServiceLocator::GetSoundSystem()
{
	if (m_pSoundSystem)
		return m_pSoundSystem.get();

	return m_pDefaultSoundSystem.get();
}

#include "ServiceLocator.h"

void ServiceLocator::RegisterSoundSystem(SoundSystem* soundSystem)
{
	// delete old service
	delete m_pSoundSystem;

	if (soundSystem)
		m_pSoundSystem = soundSystem;
	else
		m_pSoundSystem = m_pDefaultSoundSystem.get();
}

SoundSystem* ServiceLocator::GetSoundSystem()
{
	return m_pDefaultSoundSystem.get();
}

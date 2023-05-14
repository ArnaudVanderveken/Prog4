#include "ServiceLocator.h"

ServiceLocator::~ServiceLocator()
{
	delete m_pSoundSystem;
}

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
	if (m_pSoundSystem)
		return m_pSoundSystem;

	return m_pDefaultSoundSystem.get();
}

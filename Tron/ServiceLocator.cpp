#include "ServiceLocator.h"

#include <utility>


void ServiceLocator::RegisterSoundSystem(const std::shared_ptr<SoundSystem>& soundSystem)
{
		m_pSoundSystem = soundSystem;
}

SoundSystem* ServiceLocator::GetSoundSystem()
{
	if (m_pSoundSystem)
		return m_pSoundSystem.get();

	return m_pDefaultSoundSystem.get();
}

void ServiceLocator::RegisterLevelManager(const std::shared_ptr<dae::LevelManager>& levelManager)
{
	m_pLevelManager = levelManager;
}

dae::LevelManager* ServiceLocator::GetLevelManager()
{
	return m_pLevelManager.get();
}

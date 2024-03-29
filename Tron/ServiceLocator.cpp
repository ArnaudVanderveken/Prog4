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

void ServiceLocator::RegisterBulletManager(const std::shared_ptr<dae::BulletManager>& bulletManager)
{
	m_pBulletManager = bulletManager;
}

dae::BulletManager* ServiceLocator::GetBulletManager()
{
	return m_pBulletManager.get();
}

void ServiceLocator::RegisterGameManager(const std::shared_ptr<dae::GameManager>& gameManager)
{
	m_pGameManager = gameManager;
}

dae::GameManager* ServiceLocator::GetGameManager()
{
	return m_pGameManager.get();
}

void ServiceLocator::RegisterLeaderboardManager(const std::shared_ptr<dae::LeaderboardManager>& leaderboardManager)
{
	m_pLeaderboardManager = leaderboardManager;
}

dae::LeaderboardManager* ServiceLocator::GetLeaderboardManager()
{
	return m_pLeaderboardManager.get();
}

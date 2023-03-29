#include "AchievementManager.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

dae::AchievementManager::AchievementManager() noexcept
	: m_CallbackUserStatsReceived(this, &AchievementManager::OnUserStatsReceived)
	, m_CallbackUserStatsStored(this, &AchievementManager::OnUserStatsStored)
	, m_CallbackAchievementStored(this, &AchievementManager::OnAchievementStored)
	, m_iAppID(SteamUtils()->GetAppID())
	, m_iNumAchievements(int(Achievements::SIZE))
	, m_bInitialized(false)
{
	m_pAchievements = new Achievement_t[m_iNumAchievements]
	{
		_ACH_ID(int(Achievements::ACH_WIN_ONE_GAME), "Winner"),
		_ACH_ID(int(Achievements::ACH_WIN_100_GAMES), "Champion"),
		_ACH_ID(int(Achievements::ACH_TRAVEL_FAR_ACCUM), "Interstellar"),
		_ACH_ID(int(Achievements::ACH_TRAVEL_FAR_SINGLE), "Orbiter")
	};

	RequestStats();
}

dae::AchievementManager::~AchievementManager()
{
	delete[] m_pAchievements;
}

bool dae::AchievementManager::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool dae::AchievementManager::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}

void dae::AchievementManager::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Received stats and achievements from Steam\n");
			m_bInitialized = true;

			// load achievements
			for (int iAch = 0; iAch < m_iNumAchievements; ++iAch)
			{
				Achievement_t& ach = m_pAchievements[iAch];

				SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
				_snprintf(ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"name"));
				_snprintf(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"desc"));
			}
		}
		else
		{
			char buffer[128];
			_snprintf(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}

void dae::AchievementManager::OnUserStatsStored(UserStatsStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Stored stats for Steam\n");
		}
		else
		{
			char buffer[128];
			_snprintf(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}

void dae::AchievementManager::OnAchievementStored(UserAchievementStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		OutputDebugString("Stored Achievement for Steam\n");
	}
}

void dae::AchievementManager::Update()
{
}

void dae::AchievementManager::OnNotify(const Event& e)
{
	if (e.type == Event::EventType::AchievementWon)
	{
		SetAchievement("ACH_WIN_ONE_GAME");
	}
}

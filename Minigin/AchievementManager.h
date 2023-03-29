#pragma once

#include <memory>

#include "BaseComponent.h"
#include "Observer.h"
#include <steam_api.h>

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

namespace dae
{

	struct Achievement_t
	{
		int m_eAchievementID;
		const char* m_pchAchievementID;
		char m_rgchName[128];
		char m_rgchDescription[256];
		bool m_bAchieved;
		int m_iIconImage;
	};

	enum class Achievements
	{
		ACH_WIN_ONE_GAME = 0,
		ACH_WIN_100_GAMES = 1,
		ACH_TRAVEL_FAR_ACCUM = 2,
		ACH_TRAVEL_FAR_SINGLE = 3,
		SIZE
	};

	class AchievementManager : public BaseComponent, public Observer
	{
	public:
		AchievementManager() noexcept;
		~AchievementManager() override;

		AchievementManager(const AchievementManager& other) = delete;
		AchievementManager& operator=(const AchievementManager& other) noexcept = delete;
		AchievementManager(AchievementManager&& other) = delete;
		AchievementManager& operator=(AchievementManager&& other) noexcept = delete;

		void Update() override;

		void OnNotify(const Event& e) override;

		bool RequestStats();
		bool SetAchievement(const char* ID);

		STEAM_CALLBACK(AchievementManager, OnUserStatsReceived, UserStatsReceived_t,
			m_CallbackUserStatsReceived);
		STEAM_CALLBACK(AchievementManager, OnUserStatsStored, UserStatsStored_t,
			m_CallbackUserStatsStored);
		STEAM_CALLBACK(AchievementManager, OnAchievementStored,
			UserAchievementStored_t, m_CallbackAchievementStored);
		
	private:
		/* DATA MEMBERS */

		uint64 m_iAppID; // Our current AppID
		Achievement_t* m_pAchievements; // Achievements data
		int m_iNumAchievements; // The number of Achievements
		bool m_bInitialized; // Have we called Request stats and received the callback?

		/* PRIVATE METHODS */

	};
}


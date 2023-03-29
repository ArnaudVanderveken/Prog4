#pragma once


struct Event final
{
	enum class EventType
	{
		PlayerDied,
		PointScored,
		AchievementWon
	};

	EventType type;
	int playerIndex;
	int points;
};


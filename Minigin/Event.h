#pragma once


struct Event final
{
	enum class EventType
	{
		PlayerDied,
		PointScored
	};

	EventType type;
	int playerIndex;
	int points;
};


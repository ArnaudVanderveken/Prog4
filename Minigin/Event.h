#pragma once


struct Event final
{
	enum class EventType
	{
		PlayerDied
	};

	EventType type;
	int playerIndex;
};


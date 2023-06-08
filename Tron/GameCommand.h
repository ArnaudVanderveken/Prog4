#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;

	class Move : public Command
	{
	public:
		enum class Direction
		{
			Up,
			Down,
			Left,
			Right
		};

		explicit Move(GameObject* actor, Direction direction);
		~Move() override = default;
		void Execute() override;

	private:
		Direction m_Direction;
	};

	class DieCommand : public Command
	{
	public:
		explicit DieCommand(GameObject* actor);
		~DieCommand() override = default;
		void Execute() override;
	};

	class ScoreCommand : public Command
	{
	public:
		explicit ScoreCommand(GameObject* actor);
		~ScoreCommand() override = default;
		void Execute() override;
	};

	class FireCommand : public Command
	{
	public:
		enum class Direction
		{
			Up,
			Down,
			Left,
			Right
		};

		explicit FireCommand(GameObject* actor, Direction direction);
		~FireCommand() override = default;
		void Execute() override;

	private:
		Direction m_Direction;
	};
}

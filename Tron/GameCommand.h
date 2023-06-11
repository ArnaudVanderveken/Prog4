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

	class StartCommand : public Command
	{
	public:
		StartCommand() noexcept;
		~StartCommand() override = default;

		void Execute() override;
	};

	class PauseCommand : public Command
	{
	public:
		PauseCommand() noexcept;
		~PauseCommand() override = default;

		void Execute() override;
	};

	class UnpauseCommand : public Command
	{
	public:
		UnpauseCommand() noexcept;
		~UnpauseCommand() override = default;

		void Execute() override;
	};

	class QuitCommand : public Command
	{
	public:
		QuitCommand() noexcept;
		~QuitCommand() override = default;

		void Execute() override;
	};

	class SkipLevelCommand : public Command
	{
	public:
		SkipLevelCommand() noexcept;
		~SkipLevelCommand() override = default;

		void Execute() override;
	};

	class ChangeGamemode : public Command
	{
	public:
		ChangeGamemode() noexcept;
		~ChangeGamemode() override = default;

		void Execute() override;
	};

	class MuteCommand : public Command
	{
	public:
		MuteCommand() noexcept;
		~MuteCommand() override = default;

		void Execute() override;
	};
}

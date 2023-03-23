#pragma once

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		explicit Command(GameObject* actor);
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command& operator=(const Command& other) noexcept = delete;
		Command(Command&& other) = default;
		Command& operator=(Command&& other) noexcept = default;

		virtual void Execute() = 0;

	protected:
		[[nodiscard]] GameObject* GetActor() const;

	private:
		GameObject* m_pActor;
		
	};

	class MoveUp : public Command
	{
	public:
		explicit MoveUp(GameObject* actor);
		~MoveUp() override = default;
		void Execute() override;
	};

	class MoveDown : public Command
	{
	public:
		explicit MoveDown(GameObject* actor);
		~MoveDown() override = default;
		void Execute() override;
	};

	class MoveLeft : public Command
	{
	public:
		explicit MoveLeft(GameObject* actor);
		~MoveLeft() override = default;
		void Execute() override;
	};

	class MoveRight : public Command
	{
	public:
		explicit MoveRight(GameObject* actor);
		~MoveRight() override = default;
		void Execute() override;
	};

}



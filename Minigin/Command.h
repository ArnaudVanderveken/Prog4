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

}


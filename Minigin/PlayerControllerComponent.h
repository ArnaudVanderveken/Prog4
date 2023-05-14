#pragma once

#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class PlayerControllerComponent : public BaseComponent, public Subject
	{
	public:
		PlayerControllerComponent(int controllerIndex, bool useKeyboard) noexcept;
		~PlayerControllerComponent() override = default;

		PlayerControllerComponent(const PlayerControllerComponent& other) = delete;
		PlayerControllerComponent& operator=(const PlayerControllerComponent& other) noexcept = delete;
		PlayerControllerComponent(PlayerControllerComponent&& other) = delete;
		PlayerControllerComponent& operator=(PlayerControllerComponent&& other) noexcept = delete;

		void Init() override;
		void Update() override;

		[[nodiscard]] int GetPlayerIndex() const;

		void AddMovementInput(float h, float v);
		void SetSpeed(float speed);

		void Die() const;
		void ScorePoints() const;

	protected:
	private:
		/* DATA MEMBERS */
		inline static int s_NextAvailablePlayerIndex{};

		int m_PlayerIndex;
		int m_DeathClipID;

		float m_Speed{ 50.f };
		glm::vec2 m_Movement{};

		int m_ControllerIndex{};
		bool m_UseKeyboard{};

		/* PRIVATE METHODS */

		static int GetNextPlayerIndex();

		void RegisterControllerActions() const;
		void RegisterKeyboardActions() const;
		void RegisterCombinedActions() const;
	};

}



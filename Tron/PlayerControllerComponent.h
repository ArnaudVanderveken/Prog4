#pragma once

#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class RenderComponent;
	class PlayerControllerComponent final : public BaseComponent
	{
	public:
		PlayerControllerComponent(int controllerIndex, bool useKeyboard, RenderComponent* renderComponent) noexcept;
		~PlayerControllerComponent() override = default;

		PlayerControllerComponent(const PlayerControllerComponent& other) = delete;
		PlayerControllerComponent& operator=(const PlayerControllerComponent& other) noexcept = delete;
		PlayerControllerComponent(PlayerControllerComponent&& other) = delete;
		PlayerControllerComponent& operator=(PlayerControllerComponent&& other) noexcept = delete;

		[[nodiscard]] int GetPlayerIndex() const;

		void AddMovementInput(float h, float v);
		void SetSpeed(float speed);

		void Die() const;
		void ScorePoints() const;

		Subject<int> playerDied;
		Subject<int, int> pointsScored;

	protected:
		void Init() override;
		void Update() override;

	private:
		/* DATA MEMBERS */

		inline static int s_NextAvailablePlayerIndex{};

		int m_PlayerIndex;
		int m_DeathClipID;

		float m_Speed{ 50.f };
		glm::vec2 m_Movement{};

		int m_ControllerIndex{};
		bool m_UseKeyboard{};

		RenderComponent* m_pRenderComponent{};
		//uint8_t m_Orientation{};

		/* PRIVATE METHODS */

		static int GetNextPlayerIndex();

		void RegisterControllerActions() const;
		void RegisterKeyboardActions() const;
		void RegisterCombinedActions() const;
	};

}



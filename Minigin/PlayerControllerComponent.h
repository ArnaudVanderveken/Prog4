#pragma once

#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace dae
{
	class PlayerControllerComponent : public BaseComponent
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

		void AddMovementInput(float h, float v);

		void SetSpeed(float speed);

	protected:
	private:
		/* DATA MEMBERS */

		float m_Speed{ 50.f };
		glm::vec2 m_Movement{};

		int m_ControllerIndex{};
		bool m_UseKeyboard{};

		/* PRIVATE METHODS */

		void RegisterControllerActions() const;
		void RegisterKeyboardActions() const;
		void RegisterCombinedActions() const;
	};

}



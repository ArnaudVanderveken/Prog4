#pragma once

#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class RenderComponent;
	class PlayerControllerComponent final : public BaseComponent, public Observer<>
	{
	public:
		PlayerControllerComponent(int controllerIndex, bool useKeyboard, RenderComponent* bodyRenderComponent, RenderComponent* gunRenderComponent, bool countAsEnemy = false) noexcept;
		~PlayerControllerComponent() override = default;

		PlayerControllerComponent(const PlayerControllerComponent& other) = delete;
		PlayerControllerComponent& operator=(const PlayerControllerComponent& other) noexcept = delete;
		PlayerControllerComponent(PlayerControllerComponent&& other) = delete;
		PlayerControllerComponent& operator=(PlayerControllerComponent&& other) noexcept = delete;

		void SetCountAsEnemy(bool val);

		[[nodiscard]] int GetPlayerIndex() const;

		void BindActions() const;

		void AddMovementInput(float h, float v);
		void SetSpeed(float speed);

		void Die() const;
		void Fire(float h, float v);

		Subject<> playerDied;
		Subject<int> scorePoints;

		void HandleEvent() override;

	protected:
		void Init() override;
		void Update() override;

	private:
		/* DATA MEMBERS */

		inline static int s_NextAvailablePlayerIndex{};

		int m_PlayerIndex;
		int m_FireSound;

		float m_Speed{ 50.f };
		glm::vec2 m_Movement{};

		glm::vec2 m_FireInput{};
		static constexpr float FIRE_COOLDOWN{ 1.0f };
		float m_Cooldown{ FIRE_COOLDOWN };

		int m_ControllerIndex{};
		bool m_UseKeyboard{};

		RenderComponent* m_pBodyRenderComponent{};
		RenderComponent* m_pGunRenderComponent{};

		bool m_CountAsEnemy{};

		/* PRIVATE METHODS */

		static int GetNextPlayerIndex();

		void RegisterControllerActions() const;
		void RegisterKeyboardActions() const;
		void RegisterCombinedActions() const;
	};

}



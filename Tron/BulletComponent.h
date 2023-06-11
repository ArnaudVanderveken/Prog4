#pragma once
#include "BaseComponent.h"

#include <glm/glm.hpp>

namespace dae
{
    class BulletComponent final : public BaseComponent
    {
    public:
		enum class Type
		{
			Enemy,
			Player1,
			Player2
		};

	    BulletComponent(uint16_t index, Type type = Type::Enemy) noexcept;
	    ~BulletComponent() override = default;

	    BulletComponent(const BulletComponent& other) noexcept = delete;
	    BulletComponent(BulletComponent&& other) noexcept = delete;
	    BulletComponent& operator=(const BulletComponent& other) noexcept = delete;
	    BulletComponent& operator=(BulletComponent&& other) noexcept = delete;

    	[[nodiscard]] Type GetType() const;

		void SetDirection(const glm::vec2& direction);
		void SetPosition(const glm::vec2& position) const;
		void SetType(Type type);

		void Reset();

    protected:
		void Update() override;

    private:
	    /* DATA MEMBERS */

		static constexpr float BULLET_SPEED{ 96.0f };

		Type m_Type{};
		glm::vec2 m_Direction{};
		uint16_t m_BulletIndex{};

		uint8_t m_Bounces{};
		static constexpr uint8_t MAX_BOUNCES{ 5 };

	    /* PRIVATE METHODS */

		void Bounce();

    };
}

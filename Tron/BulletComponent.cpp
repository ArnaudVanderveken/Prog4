#include "BulletComponent.h"

#include "BulletManager.h"
#include "GameObject.h"
#include "LevelComponent.h"
#include "ServiceLocator.h"
#include "TimeManager.h"

dae::BulletComponent::BulletComponent(uint16_t index, Type type) noexcept
	: m_Type(type)
	, m_BulletIndex(index)
{
}

dae::BulletComponent::Type dae::BulletComponent::GetType() const
{
	return m_Type;
}

void dae::BulletComponent::SetDirection(const glm::vec2& direction)
{
	m_Direction = direction;
}

void dae::BulletComponent::SetPosition(const glm::vec2& position) const
{
	GetOwner()->SetLocalPosition({ position, 0.0f });
}

void dae::BulletComponent::SetType(Type type)
{
	m_Type = type;
}

void dae::BulletComponent::Reset()
{
	m_Bounces = MAX_BOUNCES;
}

void dae::BulletComponent::Update()
{
	const auto position = GetOwner()->GetWorldTransform().position;
	glm::vec2 offset = m_Direction * BULLET_SPEED * TimeManager::GetInstance().GetElapsedTime();
	glm::vec2 vec2Pos{ GetOwner()->GetLocalTransform().position };
	if (offset.x >= offset.y)
	{
		if (!ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->CheckBulletCollision({ vec2Pos.x + offset.x, vec2Pos.y }))
		{
			offset.x = 0;
			m_Direction.x *= -1.0f;
			Bounce();
		}
		if (!ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->CheckBulletCollision({ vec2Pos.x, vec2Pos.y + offset.y }))
		{
			offset.y = 0;
			m_Direction.y *= -1.0f;
			Bounce();
		}
	}
	else
	{
		if (!ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->CheckBulletCollision({ vec2Pos.x, vec2Pos.y + offset.y }))
		{
			offset.y = 0;
			m_Direction.y *= -1.0f;
			Bounce();
		}
		if (!ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->CheckBulletCollision({ vec2Pos.x + offset.x, vec2Pos.y }))
		{
			offset.x = 0;
			m_Direction.x *= -1.0f;
			Bounce();
		}
	}
	
	GetOwner()->SetLocalPosition(position + glm::vec3{offset, 0});
}

void dae::BulletComponent::Bounce()
{
	--m_Bounces;
	if (!m_Bounces)
		ServiceLocator::GetBulletManager()->RemoveBullet(m_BulletIndex);
}

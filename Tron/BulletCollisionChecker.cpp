#include "BulletCollisionChecker.h"

#include "GameObject.h"
#include "ServiceLocator.h"

void dae::BulletCollisionChecker::SetRules(bool p1, bool p2, bool enemy)
{
	m_IsHitByP1 = p1;
	m_IsHitByP2 = p2;
	m_IsHitByEnemy = enemy;
}

void dae::BulletCollisionChecker::LateUpdate()
{
	const auto& bullets = ServiceLocator::GetBulletManager()->GetBulletComponents();
	const glm::vec2 tankPos = GetOwner()->GetWorldTransform().position;

	for (const auto& bullet : bullets)
	{
		if (!bullet->GetOwner()->IsActive())
			continue;

		const glm::vec2 bulletPos = bullet->GetOwner()->GetWorldTransform().position;
		if ((bullet->GetType() == BulletComponent::Type::Player1 && m_IsHitByP1
			|| bullet->GetType() == BulletComponent::Type::Player2 && m_IsHitByP2
			|| bullet->GetType() == BulletComponent::Type::Enemy && m_IsHitByEnemy)
			&& IsColliding(tankPos, bulletPos))
		{
			wasHit.Notify();
			ServiceLocator::GetBulletManager()->RemoveBullet(bullet->GetIndex());
		}
	}
}

bool dae::BulletCollisionChecker::IsColliding(const glm::vec2& tankPos, const glm::vec2& bulletPos)
{
	return abs(tankPos.x - bulletPos.x) <= TANK_EXTENT && abs(tankPos.y - bulletPos.y) <= TANK_EXTENT;
}

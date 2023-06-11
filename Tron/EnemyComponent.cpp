#include "EnemyComponent.h"

#include "GameManager.h"
#include "GameObject.h"
#include "LevelComponent.h"
#include "ServiceLocator.h"
#include "TimeManager.h"

dae::EnemyComponent::EnemyComponent(bool isRecognizer) noexcept
	: m_IsRecognizer(isRecognizer)
{
	m_FireSound = ServiceLocator::GetSoundSystem()->AddClip("../Data/Sounds/Shoot.mp3");
}

void dae::EnemyComponent::HandleEvent()
{
	GetOwner()->SetActive(false);
	ServiceLocator::GetGameManager()->CheckLevelCleared();
	scorePoints.Notify(m_IsRecognizer ? 200 : 100);
}

void dae::EnemyComponent::Update()
{
	if (ServiceLocator::GetGameManager()->GetGamemode() == GameManager::GameMode::Coop)
	{
		const glm::vec2 p1Dist = ServiceLocator::GetGameManager()->GetP1Tank()->GetWorldTransform().position - GetOwner()->GetWorldTransform().position;
		const glm::vec2 p2Dist = ServiceLocator::GetGameManager()->GetP2Tank()->GetWorldTransform().position - GetOwner()->GetWorldTransform().position;
		if (glm::length(p2Dist) > glm::length(p1Dist))
			m_pTarget = ServiceLocator::GetGameManager()->GetP2Tank().get();

		else
			m_pTarget = ServiceLocator::GetGameManager()->GetP1Tank().get();
	}
	else
		m_pTarget = ServiceLocator::GetGameManager()->GetP1Tank().get();

	
}

void dae::EnemyComponent::LateUpdate()
{
	if (!m_IsRecognizer)
	{
		m_FireCooldown += TimeManager::GetInstance().GetElapsedTime();
		if (m_FireCooldown >= FIRE_COOLDOWN && CheckIsInSight(m_pTarget->GetWorldTransform().position))
		{
			glm::vec2 direction = normalize(glm::vec2{ m_pTarget->GetWorldTransform().position - GetOwner()->GetWorldTransform().position });
			if (direction.x >= direction.y)
				direction.y = 0.0f;
			else
				direction.x = 0.0f;

			ServiceLocator::GetBulletManager()->SpawnBullet(GetOwner()->GetWorldTransform().position, BulletComponent::Type::Enemy, direction);
			m_FireCooldown = 0.0f;
			ServiceLocator::GetSoundSystem()->Play(m_FireSound);
		}
	}
}

bool dae::EnemyComponent::CheckIsInSight(const glm::vec3& pos)
{
	constexpr float tileSize{ 8.0f };
	bool isInSight{ true };

	glm::vec2 testPos{ GetOwner()->GetWorldTransform().position };

	const glm::vec2 direction{ normalize(pos - GetOwner()->GetWorldTransform().position) };
	while (abs(testPos.x - pos.x) >= tileSize)
	{
		const glm::vec2 relativePos = testPos - glm::vec2{ ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->GetOwner()->GetWorldTransform().position };
		if (!ServiceLocator::GetLevelManager()->GetCurrentSceneComponent()->IsWalkableAtPixel(relativePos))
		{
			isInSight = false;
			break;
		}
		testPos += direction * tileSize;
	}

	return isInSight;
}

#pragma once

#include <vector>
#include "Transform.h"

namespace dae
{
	class BaseComponent;
	class GameObject final
	{
	public:
		GameObject(bool startActive = true);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* component);
		template<typename T> T* GetComponent() const;

		void Init() const;

		void Update() const;
		void FixedUpdate() const;
		void Render() const;

		void OnGUI() const;

		// Destroy objects
		void MarkForDelete();
		[[nodiscard]] bool IsMarkedForDelete() const;

		[[nodiscard]] const Transform& GetLocalTransform() const;
		[[nodiscard]] const Transform& GetWorldTransform();
		void SetLocalTransform(const Transform& transform);
		void SetLocalPosition(const glm::vec3& position);
		void SetLocalRotation(const glm::vec3& rotation);
		void SetLocalScale(const glm::vec3& scale);

		void SetParent(GameObject* parent, bool keepWorldTransform);

		void SetActive(bool active);

	private:
		bool m_MarkedForDelete{};
		bool m_IsActive{};

		Transform m_LocalTransform{};
		Transform m_WorldTransform{};
		bool m_DirtyWorldTransform{ true };

		std::vector<BaseComponent*> m_Components;

		GameObject* m_Parent{};
		std::vector<GameObject*> m_Children{};

		/* --- Methods --- */
		void PropagateDirtyTransform();
		void RebuildLocalTransform();
		void RebuildWorldTransform();

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	};

	template <typename T>
	inline T* GameObject::GetComponent() const
	{
		for (auto baseComp : m_Components)
			if (T* component = dynamic_cast<T*>(baseComp))
				return component;

		return nullptr;
	}

}



#pragma once

#include <vector>
#include "Transform.h"

namespace dae
{
	class BaseComponent;
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* component);
		template<typename T> T* GetComponent() const;
		template<typename T> void RemoveComponent();
		
		void Update() const;
		void FixedUpdate() const;
		void Render() const;

		void OnGUI() const;

		[[nodiscard]] const Transform& GetLocalTransform() const;
		[[nodiscard]] const Transform& GetWorldTransform();
		void SetLocalTransform(const Transform& transform);
		void SetLocalPosition(const glm::vec3& position);
		void SetLocalRotation(const glm::vec3& rotation);
		void SetLocalScale(const glm::vec3& scale);

		void SetParent(GameObject* parent, bool keepWorldTransform);

	private:
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

	template <typename T>
	inline void GameObject::RemoveComponent()
	{
		for (auto baseComp : m_Components)
		{
			T* component = dynamic_cast<T*>(baseComp);
			if (component)
			{
				delete component;
				component = nullptr;

				//Remove from vector
				component = m_Components.back();
				m_Components.pop_back();

				return;
			}
		}
	}
}



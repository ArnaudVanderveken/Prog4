#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		explicit BaseComponent(dae::GameObject* parentGameObject) noexcept;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) noexcept = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		void SetActive(bool newActive);

	protected:
		dae::GameObject* m_pGameObject{};
		bool m_IsActive{ true };
		
	};
}



#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
		friend class GameObject;

	public:
		explicit BaseComponent() noexcept = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) noexcept = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		virtual void OnGUI() = 0;

		void SetActive(bool newActive);
		[[nodiscard]] bool IsActive() const;

		[[nodiscard]] GameObject* GetOwner() const;

	private:
		void SetOwner(GameObject* owner);
		GameObject* m_pOwner{};

		bool m_IsActive{ true };
	};
}



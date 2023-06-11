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

		virtual void Init() {}

		virtual void Update() = 0;
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}
		virtual void Render() const {}

		virtual void OnGUI() {}

		void SetActive(bool newActive);
		[[nodiscard]] bool IsActive() const;

		[[nodiscard]] GameObject* GetOwner() const;

	protected:
		bool m_IsActive{ true };

	private:
		void SetOwner(GameObject* owner);
		GameObject* m_pOwner{};
	};
}



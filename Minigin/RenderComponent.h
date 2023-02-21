#pragma once
#include "BaseComponent.h"

#include <string>
#include <memory>

namespace dae
{
	class Texture2D;

	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(const std::string& fileName, GameObject* owner);
		~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) noexcept = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

	private:
		std::shared_ptr<Texture2D> m_TexturePtr{};
	};
}



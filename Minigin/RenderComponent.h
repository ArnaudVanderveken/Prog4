#pragma once
#include "BaseComponent.h"

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class Texture2D;

	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(const std::string& fileName, const glm::vec2& offset = {}, float angle = 0.0f);
		~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) noexcept = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnGUI() override;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& texture);

		void SetOffset(const glm::vec2& offset);
		void SetAngle(float angle);

	private:
		std::shared_ptr<Texture2D> m_TexturePtr{};

		glm::vec2 m_Offset;
		float m_Angle;
	};
}



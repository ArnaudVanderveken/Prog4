#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include <SDL.h>

namespace dae
{
	class Font;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const SDL_Color& color, std::shared_ptr<Font> font, GameObject* owner);
		~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent& operator=(const TextComponent& other) noexcept = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

	private:
		bool m_NeedsToUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_FontPtr;

		SDL_Color m_Color;
	};
}



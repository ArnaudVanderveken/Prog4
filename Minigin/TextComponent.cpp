#include "TextComponent.h"

#include <SDL_ttf.h>
#include <stdexcept>

#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(const std::string& text, const SDL_Color& color, std::shared_ptr<dae::Font> font, dae::GameObject* owner)
	: BaseComponent{ owner }
	, m_NeedsToUpdate{ true }
	, m_Text{ text }
	, m_FontPtr{ font }
	, m_Color{ color }
{
}

void dae::TextComponent::Update()
{
	if (!m_IsActive)
		return;

	if (!m_NeedsToUpdate)
		return;

	const auto surf = TTF_RenderText_Blended(m_FontPtr->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	const auto newTexture = std::make_shared<Texture2D>(texture);

	if (const auto renderComp = m_pGameObject->GetComponent<RenderComponent>())
		renderComp->SetTexture(newTexture);

	m_NeedsToUpdate = false;
}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::Render() const
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsToUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsToUpdate = true;
}
#include "Keyboard.h"


void dae::Keyboard::Update()
{
	m_CurrentState = SDL_GetKeyboardState(nullptr);
}

void dae::Keyboard::Reset()
{
	m_KeyDown.clear();
	m_KeyUp.clear();
}

void dae::Keyboard::AddDown(SDL_Scancode key)
{
	m_KeyDown.emplace_back(key);
}

void dae::Keyboard::AddUp(SDL_Scancode key)
{
	m_KeyUp.emplace_back(key);
}

bool dae::Keyboard::IsDown(SDL_Scancode key) const
{
	return std::ranges::find(m_KeyDown, key) != m_KeyDown.end();
}

bool dae::Keyboard::IsUp(SDL_Scancode key) const
{
	return std::ranges::find(m_KeyUp, key) != m_KeyUp.end();
}

bool dae::Keyboard::IsPressed(SDL_Scancode key) const
{
	return m_CurrentState[key];
}

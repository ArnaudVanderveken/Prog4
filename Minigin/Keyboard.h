#pragma once

#include <vector>
#include <SDL.h>

namespace dae
{
	class Keyboard final
	{
	public:

		Keyboard() noexcept = default;
		~Keyboard() = default;

		Keyboard(const Keyboard& other) noexcept = delete;
		Keyboard& operator=(const Keyboard& other) noexcept = delete;
		Keyboard(Keyboard&& other) noexcept = delete;
		Keyboard& operator=(Keyboard&& other) noexcept = delete;

		void Update();

		void Reset();
		void AddDown(SDL_Scancode key);
		void AddUp(SDL_Scancode key);

		[[nodiscard]] bool IsDown(SDL_Scancode key) const;
		[[nodiscard]] bool IsUp(SDL_Scancode key) const;
		[[nodiscard]] bool IsPressed(SDL_Scancode key) const;

	private:
		const Uint8* m_CurrentState{};
		std::vector<SDL_Scancode> m_KeyDown;
		std::vector<SDL_Scancode> m_KeyUp;
	};
}



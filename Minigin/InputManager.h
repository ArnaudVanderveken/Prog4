#pragma once
#include "Singleton.h"

#include <array>
#include <memory>
#include <vector>

#include "Command.h"
#include "Controller.h"
#include "Keyboard.h"

namespace dae
{
	class InputAction final
	{
	public:
		enum class ActionType
		{
			Down,
			Up,
			Pressed
		};

		InputAction(std::shared_ptr<Command> command, ActionType action, Controller::ButtonID button, int controllerIndex, SDL_Scancode keyboardKey) noexcept;
		~InputAction() = default;

		InputAction(const InputAction& other) noexcept = delete;
		InputAction& operator=(const InputAction& other) noexcept = delete;
		InputAction(InputAction&& other) noexcept = default;
		InputAction& operator=(InputAction&& other) noexcept = default;

		void Trigger() const;

		[[nodiscard]] ActionType GetType() const;
		[[nodiscard]] Controller::ButtonID GetControllerButton() const;
		[[nodiscard]] int GetControllerIndex() const;
		[[nodiscard]] SDL_Scancode GetKeyboardKey() const;

	private:
		/* DATA MEMBERS */

		std::shared_ptr<Command> m_pCommand;
		ActionType m_Type;
		Controller::ButtonID m_Button;
		int m_ControllerIndex;
		SDL_Scancode m_KeyboardKey;

		/* PRIVATE METHODS */
		
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() noexcept;
		~InputManager() override = default;
		bool ProcessInput();

		void RegisterAction(std::shared_ptr<Command> command, InputAction::ActionType action, Controller::ButtonID button, int controllerIndex, SDL_Scancode keyboardKey);
		void RegisterAction(std::shared_ptr<Command> command, InputAction::ActionType action, Controller::ButtonID button, int controllerIndex);
		void RegisterAction(std::shared_ptr<Command> command, InputAction::ActionType action, SDL_Scancode keyboardKey);
		void ClearActions();

	private:
		std::array<std::unique_ptr<Controller>, 2> m_Controllers;
		Keyboard m_Keyboard;

		std::vector<InputAction> m_Actions;
	};

}

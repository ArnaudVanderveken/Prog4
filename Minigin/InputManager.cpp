#include <SDL.h>

#include <utility>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

dae::InputAction::InputAction(std::shared_ptr<Command> command, ActionType action, Controller::ButtonID button, int controllerIndex, SDL_Scancode keyboardKey) noexcept
	: m_pCommand(std::move(command))
	, m_Type(action)
	, m_Button(button)
	, m_ControllerIndex(controllerIndex)
	, m_KeyboardKey(keyboardKey)
{
}

void dae::InputAction::Trigger() const
{
	m_pCommand->Execute();
}

dae::InputAction::ActionType dae::InputAction::GetType() const
{
	return m_Type;
}

dae::Controller::ButtonID dae::InputAction::GetControllerButton() const
{
	return m_Button;
}

int dae::InputAction::GetControllerIndex() const
{
	return m_ControllerIndex;
}

SDL_Scancode dae::InputAction::GetKeyboardKey() const
{
	return m_KeyboardKey;
}

dae::InputManager::InputManager() noexcept
{
	for (int i{}; i < int(m_Controllers.size()); ++i)
		m_Controllers[i] = std::make_unique<Controller>(i);
}

bool dae::InputManager::ProcessInput()
{
	m_Keyboard.Reset();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return false;
		
		if (e.type == SDL_KEYDOWN)
			m_Keyboard.AddDown(e.key.keysym.scancode);
		
		if (e.type == SDL_KEYUP)
			m_Keyboard.AddUp(e.key.keysym.scancode);

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		
		// ImGui events
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	m_Keyboard.Update();

	for (const auto& controller : m_Controllers)
		controller->Update();

	for (const auto& action : m_Actions)
	{
		switch (action.GetType())
		{
		case InputAction::ActionType::Down:
			if (action.GetControllerButton() && m_Controllers[action.GetControllerIndex()]->IsDown(action.GetControllerButton()))
				action.Trigger();
			else if (action.GetKeyboardKey() && m_Keyboard.IsDown(action.GetKeyboardKey()))
				action.Trigger();

			break;

		case InputAction::ActionType::Up:
			if (action.GetControllerButton() && m_Controllers[action.GetControllerIndex()]->IsUp(action.GetControllerButton()))
				action.Trigger();
			else if (action.GetKeyboardKey() && m_Keyboard.IsUp(action.GetKeyboardKey()))
				action.Trigger();
			break;

		case InputAction::ActionType::Pressed:
			if (action.GetControllerButton() && m_Controllers[action.GetControllerIndex()]->IsPressed(action.GetControllerButton()))
				action.Trigger();
			else if (action.GetKeyboardKey() && m_Keyboard.IsPressed(action.GetKeyboardKey()))
				action.Trigger();
			break;

		}
	}

	return true;
}

void dae::InputManager::RegisterAction(std::shared_ptr<Command> command, InputAction::ActionType action, Controller::ButtonID button, int controllerIndex, SDL_Scancode keyboardKey)
{
	m_Actions.emplace_back(InputAction{std::move(command), action, button, controllerIndex, keyboardKey });
}

void dae::InputManager::RegisterAction(std::shared_ptr<Command> command, InputAction::ActionType action, Controller::ButtonID button, int controllerIndex)
{
	m_Actions.emplace_back(InputAction{ std::move(command), action, button, controllerIndex, SDL_SCANCODE_UNKNOWN });
}

void dae::InputManager::RegisterAction(std::shared_ptr<Command> command, InputAction::ActionType action, SDL_Scancode keyboardKey)
{
	m_Actions.emplace_back(InputAction{ std::move(command), action, Controller::ButtonID::None, -1, keyboardKey });
}

void dae::InputManager::ClearActions()
{
	m_Actions.clear();
}

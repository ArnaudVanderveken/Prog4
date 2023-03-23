#include "Controller.h"

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

using namespace dae;

class Controller::ControllerImpl
{
public:
	explicit ControllerImpl(int controllerIndex);
	virtual ~ControllerImpl() = default;

	ControllerImpl(const ControllerImpl& other) = delete;
	ControllerImpl& operator=(const ControllerImpl& other) noexcept = delete;
	ControllerImpl(ControllerImpl&& other) = delete;
	ControllerImpl& operator=(ControllerImpl&& other) noexcept = delete;

	virtual void Update() = 0;

	[[nodiscard]] bool IsActive() const;

	[[nodiscard]] virtual bool IsDown(ButtonID id) const = 0;
	[[nodiscard]] virtual bool IsUp(ButtonID id) const = 0;
	[[nodiscard]] virtual bool IsPressed(ButtonID id) const = 0;

protected:
	int m_ControllerIndex;
	bool m_IsActive{};

};

class XInputController final : public Controller::ControllerImpl
{
public:
	explicit XInputController(int controllerIndex) noexcept;
	~XInputController() override = default;

	XInputController(const XInputController& other) = delete;
	XInputController& operator=(const XInputController& other) noexcept = delete;
	XInputController(XInputController&& other) = delete;
	XInputController& operator=(XInputController&& other) noexcept = delete;

	void Update() override;

	[[nodiscard]] bool IsDown(Controller::ButtonID id) const override;
	[[nodiscard]] bool IsUp(Controller::ButtonID id) const override;
	[[nodiscard]] bool IsPressed(Controller::ButtonID id) const override;

private:
	/* DATA MEMBERS */

	XINPUT_STATE m_CurrentState{}, m_PreviousState{};
	WORD m_ButtonPressed{}, m_ButtonReleased{};

	/* PRIVATE METHODS */
	
};

Controller::ControllerImpl::ControllerImpl(int controllerIndex)
	: m_ControllerIndex(controllerIndex)
{
}

bool Controller::ControllerImpl::IsActive() const
{
	return m_IsActive;
}

XInputController::XInputController(int controllerIndex) noexcept
	: ControllerImpl(controllerIndex)
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void XInputController::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	const DWORD result = XInputGetState(m_ControllerIndex, &m_CurrentState);

	m_IsActive = result == ERROR_SUCCESS;

	if (!m_IsActive)
		return;

	const auto changes = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonPressed = changes & m_CurrentState.Gamepad.wButtons;
	m_ButtonReleased = changes & ~(m_CurrentState.Gamepad.wButtons);
}

bool XInputController::IsDown(Controller::ButtonID id) const
{
	return m_IsActive && m_ButtonPressed & id;
}

bool XInputController::IsUp(Controller::ButtonID id) const
{
	return m_IsActive && m_ButtonReleased & id;
}

bool XInputController::IsPressed(Controller::ButtonID id) const
{
	return m_IsActive && m_CurrentState.Gamepad.wButtons & id;
}

void Controller::Update() const
{
	m_pImpl->Update();
}

bool Controller::IsDown(ButtonID id) const
{
	return m_pImpl->IsDown(id);
}

bool Controller::IsUp(ButtonID id) const
{
	return m_pImpl->IsUp(id);
}

bool Controller::IsPressed(ButtonID id) const
{
	return m_pImpl->IsPressed(id);
}

Controller::Controller(int controllerIndex)
{
	m_pImpl = new XInputController(controllerIndex);
}

Controller::~Controller()
{
	delete m_pImpl;
}

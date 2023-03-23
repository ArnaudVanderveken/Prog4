#pragma once


namespace dae
{
	class Controller final
	{
	public:
		class ControllerImpl;
		
		enum ButtonID
		{
			None = 0x0000,
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			FaceButtonDown = 0x1000,
			FaceButtonRight = 0x2000,
			FaceButtonLeft = 0x4000,
			FaceButtonUp = 0x8000,
		};

		void Update() const;

		[[nodiscard]] bool IsDown(ButtonID id) const;
		[[nodiscard]] bool IsUp(ButtonID id) const;
		[[nodiscard]] bool IsPressed(ButtonID id) const;

		explicit Controller(int controllerIndex);
		~Controller();

	private:
		ControllerImpl* m_pImpl{};

	};
}

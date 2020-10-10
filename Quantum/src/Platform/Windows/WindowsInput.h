#pragma once

#include <Quantum/Input.h>

namespace Quantum {

	class QUANTUM_API WindowsInput : public Input
	{
	protected:
		//Key
		virtual bool IsKeyPressedImpl(int keycode) override;
		//Mouse
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}
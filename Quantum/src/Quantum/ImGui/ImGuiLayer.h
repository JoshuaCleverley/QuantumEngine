#pragma once

#include <Quantum/Layer.h>
#include <Quantum/Events/MouseEvent.h>
#include <Quantum/Events/ApplicationEvent.h>
#include <Quantum/Events/KeyEvent.h>

namespace Quantum {

	class QUANTUM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttatch()override;
		virtual void OnDetatch() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time;
	};
}
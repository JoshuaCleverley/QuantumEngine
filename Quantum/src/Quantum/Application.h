#pragma once

#include "Window.h"
#include "Quantum/LayerStack.h"
#include "Quantum/Events/Event.h"
#include "Quantum/Events/ApplicationEvent.h"

namespace Quantum {

	class QUANTUM_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application* CreateApplication();
}


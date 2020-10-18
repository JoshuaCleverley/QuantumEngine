#pragma once

#include <Quantum/Window.h>
#include <Quantum/LayerStack.h>
#include <Quantum/Events/Event.h>
#include <Quantum/Events/ApplicationEvent.h>

#include <Quantum/ImGui/ImGuiLayer.h>

#include <Quantum/Renderer/Shader.h>
#include <Quantum/Renderer/Buffer.h>
#include <Quantum/Renderer/VertexArray.h>
#include <Quantum/Renderer/OrthographicCamera.h>

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

		static Application& Get() { return *s_Instance;  } 
		inline Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		static Application* s_Instance;
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}


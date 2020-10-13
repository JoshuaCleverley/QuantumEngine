#pragma once

#include <Quantum/Window.h>
#include <Quantum/LayerStack.h>
#include <Quantum/Events/Event.h>
#include <Quantum/Events/ApplicationEvent.h>

#include <Quantum/ImGui/ImGuiLayer.h>

#include <Quantum/Renderer/Shader.h>

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}


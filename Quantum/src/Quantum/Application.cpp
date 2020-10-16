#include <qupch.h>

#include <Quantum/Application.h>
#include <Quantum/Renderer/Renderer.h>

#include <Quantum/Input.h>


namespace Quantum {

	Application* Application::s_Instance = nullptr;

	

	Application::Application()
	{
		QU_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Trainagle
		float vertices[3 * 7] = {
			/* Position */ -0.3f, -0.7f, 0.0f, /* Colour */ 0.8359f, 0.0078f, 0.4375f, 1.0f,
			/* Position */  0.5f, -0.5f, 0.0f, /* Colour */ 0.6055f, 0.3086f, 0.5859f, 1.0f,
			/* Position */  0.0f,  0.5f, 0.0f, /* Colour */ 0.0000f, 0.2188f, 0.6563f, 1.0f
		};
		
		m_VertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Colour", }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[1 * 3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec4 v_Colour;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				v_Colour = a_Colour;
			}
		)";
		
		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec4 v_Colour;

			void main()
			{
				color = v_Colour;
			}
		)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	void Application::Run()
	{

		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, .1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();
			{
				m_Shader->Bind();
				Renderer::Submit(m_VertexArray);
			}
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}

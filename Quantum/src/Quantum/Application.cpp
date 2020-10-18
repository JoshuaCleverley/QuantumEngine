#include <qupch.h>

#include <Quantum/Application.h>

#include <Quantum/Renderer/Renderer.h>
#include <Quantum/Input.h>
#include <Quantum/KeyCodes.h>
#include <Quantum/Colors.h>
namespace Quantum {

	Application* Application::s_Instance = nullptr;

	

	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		QU_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Triangle
		float vertices[4 * 7] = {
			/* Position */ -0.7f,  0.7f, 0.0f, /* Colour */ QU_COL_PURPLE, 1.0f,
			/* Position */  0.7f,  0.7f, 0.0f, /* Colour */ QU_COL_MAROON, 1.0f,
			/* Position */  0.7f, -0.7f, 0.0f, /* Colour */ QU_COL_OLIVE, 1.0f,
			/* Position */ -0.7f, -0.7f, 0.0f, /* Colour */ QU_COL_CYAN, 1.0f,
		};
		
		m_VertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Colour", }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[2 * 3] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			uniform mat4 u_ViewProjection;

			out vec4 v_Colour;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
			// Camera move code
			float speed = 0.05f;
			glm::vec2 move = glm::vec2();
			if (Input::IsKeyPressed(QU_KEY_LEFT)) {
				move.x -= speed;
			}
			if (Input::IsKeyPressed(QU_KEY_RIGHT)) {
				move.x += speed;
			}
			if (Input::IsKeyPressed(QU_KEY_UP)) {
				move.y += speed;
			}
			if (Input::IsKeyPressed(QU_KEY_DOWN)) {
				move.y -= speed;
			}
			glm::vec3 position = m_Camera.GetPosition();
			position.x += move.x;
			position.y += move.y;
			m_Camera.SetPosition(position);

			// Renderer 
			RenderCommand::SetClearColor({ QU_COL_GREY, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene(m_Camera);
			{
				Renderer::Submit(m_Shader, m_VertexArray);
			}
			Renderer::EndScene();

			// Layers
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

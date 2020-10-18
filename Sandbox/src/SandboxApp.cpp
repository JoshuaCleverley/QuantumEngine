#include <Quantum.h>
#include <imgui/imgui.h>

class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		// Triangle
		float vertices[4 * 7] = {
			/* Position */ -0.7f,  0.7f, 0.0f, /* Colour */ QU_COL_PURPLE, 1.0f,
			/* Position */  0.7f,  0.7f, 0.0f, /* Colour */ QU_COL_MAROON, 1.0f,
			/* Position */  0.7f, -0.7f, 0.0f, /* Colour */ QU_COL_OLIVE, 1.0f,
			/* Position */ -0.7f, -0.7f, 0.0f, /* Colour */ QU_COL_CYAN, 1.0f,
		};

		m_VertexArray.reset(Quantum::VertexArray::Create());

		std::shared_ptr<Quantum::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Quantum::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Quantum::ShaderDataType::Float3, "a_Position" },
			{ Quantum::ShaderDataType::Float4, "a_Colour", }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[2 * 3] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Quantum::IndexBuffer> indexBuffer;
		indexBuffer.reset(Quantum::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

		m_Shader.reset(new Quantum::Shader(vertexSource, fragmentSource));
	}

	void OnUpdate() override
	{
		// Camera move code
		float speed = 0.05f;
		glm::vec2 move = glm::vec2();
		if (Quantum::Input::IsKeyPressed(QU_KEY_LEFT)) 
			move.x -= speed;
		if (Quantum::Input::IsKeyPressed(QU_KEY_RIGHT)) 
			move.x += speed;
		if (Quantum::Input::IsKeyPressed(QU_KEY_UP)) 
			move.y += speed;
		if (Quantum::Input::IsKeyPressed(QU_KEY_DOWN)) 
			move.y -= speed;
		
		glm::vec3 position = m_Camera.GetPosition();
		position.x += move.x;
		position.y += move.y;
		m_Camera.SetPosition(position);

		// Renderer 
		Quantum::RenderCommand::SetClearColor({ QU_COL_DARK_GREY, 1.0f });
		Quantum::RenderCommand::Clear();

		Quantum::Renderer::BeginScene(m_Camera);
		{
			Quantum::Renderer::Submit(m_Shader, m_VertexArray);
		}
		Quantum::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(Quantum::Event& e) override
	{
	}

private:
	std::shared_ptr<Quantum::Shader> m_Shader;
	std::shared_ptr<Quantum::VertexArray> m_VertexArray;

	Quantum::OrthographicCamera m_Camera;
};

class Sandbox : public Quantum::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Quantum::Application* Quantum::CreateApplication()
{
	return new Sandbox();
}
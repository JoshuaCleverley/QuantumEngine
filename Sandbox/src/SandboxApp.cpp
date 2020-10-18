#include <Quantum.h>
#include <imgui/imgui.h>
#include <glm/ext/matrix_transform.hpp>

class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_SquarePosition(1.0f)
	{
		float vertices[4 * 7] = {
			/* Position */ -0.5f,  0.5f, 0.0f, /* Colour */ QU_COL_PURPLE, 1.0f,
			/* Position */  0.5f,  0.5f, 0.0f, /* Colour */ QU_COL_MAROON, 1.0f,
			/* Position */  0.5f, -0.5f, 0.0f, /* Colour */ QU_COL_OLIVE, 1.0f,
			/* Position */ -0.5f, -0.5f, 0.0f, /* Colour */ QU_COL_CYAN, 1.0f,
		};

		m_SquareVertexArray.reset(Quantum::VertexArray::Create());

		std::shared_ptr<Quantum::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Quantum::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Quantum::ShaderDataType::Float3, "a_Position" },
			{ Quantum::ShaderDataType::Float4, "a_Colour", }
			});
		m_SquareVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[2 * 3] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Quantum::IndexBuffer> indexBuffer;
		indexBuffer.reset(Quantum::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Colour;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_SquareShader.reset(new Quantum::Shader(vertexSource, fragmentSource));
	}

	void OnUpdate(Quantum::Timestep ts) override
	{
		//QU_TRACE("Delta Time: {0}s ({0}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		// Move camera
		glm::vec2 move = glm::vec2();
		if (Quantum::Input::IsKeyPressed(QU_KEY_LEFT)) 
			move.x -= m_CameraMoveSpeed * ts;
		if (Quantum::Input::IsKeyPressed(QU_KEY_RIGHT)) 
			move.x += m_CameraMoveSpeed * ts;
		if (Quantum::Input::IsKeyPressed(QU_KEY_UP)) 
			move.y += m_CameraMoveSpeed * ts;
		if (Quantum::Input::IsKeyPressed(QU_KEY_DOWN)) 
			move.y -= m_CameraMoveSpeed * ts;
		glm::vec3 position = m_Camera.GetPosition();
		position.x += move.x;
		position.y += move.y;
		m_Camera.SetPosition(position);

		// Renderer 
		Quantum::RenderCommand::SetClearColor({ QU_COL_DARK_GREY, 1.0f });
		Quantum::RenderCommand::Clear();

		Quantum::Renderer::BeginScene(m_Camera);
		{
			//Quantum::Renderer::Submit(m_SquareShader, m_SquareVertexArray, squareTransform);
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Quantum::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);
				}
			}
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
	std::shared_ptr<Quantum::Shader> m_SquareShader;
	std::shared_ptr<Quantum::VertexArray> m_SquareVertexArray;

	Quantum::OrthographicCamera m_Camera;
	float m_CameraMoveSpeed = 5.0f;
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
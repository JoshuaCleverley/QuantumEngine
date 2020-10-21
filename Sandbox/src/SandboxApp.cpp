#include <Quantum.h>
#include <imgui/imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <glm\gtc\type_ptr.hpp>

class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) 
	{
		float vertices[4 * 3] = {
			/* Position */ -0.5f,  0.5f, 0.0f,
			/* Position */  0.5f,  0.5f, 0.0f,
			/* Position */  0.5f, -0.5f, 0.0f,
			/* Position */ -0.5f, -0.5f, 0.0f,
		};

		m_SquareVertexArray.reset(Quantum::VertexArray::Create());

		std::shared_ptr<Quantum::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Quantum::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Quantum::ShaderDataType::Float3, "a_Position" },
		});
		m_SquareVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[2 * 3] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Quantum::IndexBuffer> indexBuffer;
		indexBuffer.reset(Quantum::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(indexBuffer);

		std::string flatColorVertexShaderSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragmentShaderSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Quantum::Shader::CreateShader(flatColorVertexShaderSource, flatColorFragmentShaderSource));
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

			std::dynamic_pointer_cast<Quantum::OpenGLShader>(m_FlatColorShader)->Bind();
			std::dynamic_pointer_cast<Quantum::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

			glm::mat4 transform(1.0f);
			Quantum::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
		}
		Quantum::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColor));
		
		ImGui::End();
	}

	void OnEvent(Quantum::Event& e) override
	{
	}

private:
	std::shared_ptr<Quantum::Shader> m_FlatColorShader;
	std::shared_ptr<Quantum::VertexArray> m_SquareVertexArray; 

	glm::vec3 m_SquareColor = { QU_COL_CYAN };

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
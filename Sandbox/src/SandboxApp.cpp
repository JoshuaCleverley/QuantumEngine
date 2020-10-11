#include <Quantum.h>
#include <imgui/imgui.h>

class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Quantum::Input::IsKeyPressed(QU_KEY_ENTER))
		{
			QU_TRACE("Enter key is pressed");
		}
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Quantum::Event& e) override
	{
		//QU_TRACE("{0}", e);
	}
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
#include "Quantum.h"

class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		QU_INFO("ExampleLayer::Update");
	}

	void OnEvent(Quantum::Event& e) override
	{
		QU_TRACE("{0}", e);
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
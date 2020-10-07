#include "Quantum.h"

class Sandbox : public Quantum::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Quantum::Application* Quantum::CreateApplication()
{
	return new Sandbox();
}
#include "Quantum/Application.h"

#include "Quantum/Events/ApplicationEvent.h"
#include "Quantum/Log.h"

namespace Quantum {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		QU_TRACE(e);

		while (true);
	}
}

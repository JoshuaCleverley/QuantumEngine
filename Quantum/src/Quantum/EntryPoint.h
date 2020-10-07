#pragma once

#ifdef QU_PLATFORM_WINDOWS

extern Quantum::Application* Quantum::CreateApplication();

int main(int argc, char** argv) 
{
	Quantum::Log::Init();

	QU_CORE_TRACE("Logging initialisation complete");


	auto app = Quantum::CreateApplication();
	app->Run();
	delete app;
}

#endif
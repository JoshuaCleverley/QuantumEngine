#pragma once

#ifdef QU_PLATFORM_WINDOWS

extern Quantum::Application* Quantum::CreateApplication();

int main(int argc, char** argv) {
	printf("Quantum Engine\n");
	auto app = Quantum::CreateApplication();
	app->Run();
	delete app;
}

#endif
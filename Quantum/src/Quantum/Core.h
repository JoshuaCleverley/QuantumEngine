#pragma once

#ifdef QU_PLATFORM_WINDOWS
	#ifdef QU_BUILD_DLL
		#define QUANTUM_API __declspec(dllexport)
	#else
		#define QUANTUM_API __declspec(dllimport)
	#endif
#else
	#error Quantum only supports Windows OS
#endif
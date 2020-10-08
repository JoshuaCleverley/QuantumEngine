#pragma once

#include "qupch.h"

#ifdef QU_PLATFORM_WINDOWS
	#ifdef QU_BUILD_DLL
		#define QUANTUM_API __declspec(dllexport)
	#else
		#define QUANTUM_API __declspec(dllimport)
	#endif
#else
	#error Quantum only supports Windows OS
#endif

#ifdef QU_ENABLE_ASSERTS
	#define QU_ASSERT(x, ...)	   { if(!(x)) { QU_ERROR(	  "Assertion Fails: {0}", __VA_ARGS__); __debugbreak(); }}
	#define QU_CORE_ASSERT(x, ...) { if(!(x)) { QU_CORE_ERROR("Assertion Fails: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define QU_ASSERT(x, ...)
	#define QU_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
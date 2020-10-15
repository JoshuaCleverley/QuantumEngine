#pragma once

#include <qupch.h>

#ifdef QU_PLATFORM_WINDOWS
	#ifdef QU_DYNAMIC_LINK
		#ifdef QU_BUILD_DLL
			#define QUANTUM_API __declspec(dllexport)
		#else
			#define QUANTUM_API __declspec(dllimport)
		#endif
	#else
		#define QUANTUM_API
	#endif
#else
	#error Quantum only supports Windows OS
#endif

#ifdef QU_DEBUG
	#define QU_ENABLE_ASSERTS
#endif

#ifdef QU_ENABLE_ASSERTS
	#define QU_ASSERT(x, ...)	   { if(!(x)) { QU_CRITICAL(	  "Assertion Fails: {0}", __VA_ARGS__); __debugbreak(); }}
	#define QU_CORE_ASSERT(x, ...) { if(!(x)) { QU_CORE_CRITICAL("Assertion Fails: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define QU_ASSERT(x, ...)
	#define QU_CORE_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)
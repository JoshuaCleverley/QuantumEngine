#pragma once

#include "Quantum/Core.h"
#include "Quantum/Events/Event.h"

namespace Quantum {

	class QUANTUM_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttatch() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; 
	};
}

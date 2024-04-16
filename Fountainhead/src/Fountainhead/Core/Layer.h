#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Timestep.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}//当层推入栈，成为程序的一部分时，被Attached(链接)
		virtual void OnDetach() {}//当层被移除时，Detach(分离)
		virtual void OnUpdate(Timestep ts) {}//在层更新时由应用程序调用，应当每帧调用一次
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}//层得到事件时，我们从这里接收

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
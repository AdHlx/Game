#pragma once

#include "Fountainhead/Core/Layer.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/KeyEvent.h"
#include "Fountainhead/Events/MouseEvent.h"


namespace Fountainhead {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
#pragma once

#include"Reptile/Layer.h"

#include"Reptile/Events/ApplicationEvent.h"
#include"Reptile/Events/KeyEvent.h"
#include"Reptile/Events/MouseEvent.h"

namespace Reptile {

	class REPTILE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnImGuiRender()override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}


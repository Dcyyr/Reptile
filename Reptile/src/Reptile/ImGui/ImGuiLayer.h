#pragma once

#include "Reptile/Core/Layer.h"

#include "Reptile/Events/ApplicationEvent.h"
#include "Reptile/Events/KeyEvent.h"
#include "Reptile/Events/MouseEvent.h"

namespace Reptile {

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
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
		virtual void OnEvent(Event& e) override;

		void BlockEvent(bool block){  m_BlockEvents = block;}
		void Begin();
		void End();
	private:
		bool m_BlockEvents = true;

		float m_Time = 0.0f;
	};

}
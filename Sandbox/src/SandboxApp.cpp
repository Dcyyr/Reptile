#include"Reptile.h"


class ExampleLayer : public Reptile::Layer
{
public:
	ExampleLayer() 
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Reptile::Input::IsKeyPressed(RP_KEY_TAB))
			RP_TRACE("tab key is pressed!");
	}

	void OnEvent(Reptile::Event& event) override
	{
		if (event.GetEventType() == Reptile::EventType::KeyPressed)
		{
			Reptile::KeyPressedEvent& e = (Reptile::KeyPressedEvent&)event;
			if (e.GetKeyCode() == RP_KEY_TAB)
				RP_TRACE("tab key is pressed(event)!");
			RP_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox :public Reptile::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Reptile::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Reptile::Application* Reptile::CreateApplication()
{
	return new Sandbox();
}
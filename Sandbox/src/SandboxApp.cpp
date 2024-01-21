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
		RP_INFO("ExampleLayer::Updata");
	}

	void OnEvent(Reptile::Event& event) override
	{
		RP_TRACE("{0}", event);
	}
};

class Sandbox :public Reptile::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Reptile::Application* Reptile::CreateApplication()
{
	return new Sandbox();
}
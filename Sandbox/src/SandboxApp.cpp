#include "Reptile.h"
#include "Reptile/Core/EntryPoint.h"

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Reptile::Application
{
public:
	Sandbox()
		:Application("Sandbox ")
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Reptile::Application* Reptile::CreateApplication()
{
	return new Sandbox();
}
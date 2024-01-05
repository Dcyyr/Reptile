#include"Reptile.h"

class Sandbox :public Reptile::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Reptile::Application* Reptile::CreateApplication()
{
	return new Sandbox();
}
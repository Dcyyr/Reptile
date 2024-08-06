#include "Reptile.h"
#include "Reptile/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Reptile {

	class ReptileEditor : public Application
	{
	public:
		ReptileEditor()
			:Application("Reptile Editor")
		{
			PushLayer(new EditorLayer()); 
		}

		~ReptileEditor()
		{

		}

	};

	Application* CreateApplication()
	{
		return new ReptileEditor();
	}
}
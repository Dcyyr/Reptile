#pragma once

#include"Reptile/Core/Core.h"

namespace Reptile {

	class REPTILE_API Input
	{
	
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float>GetMousePosition();
			
		static float GetMouseX();
		static float GetMouseY();

	
	};
}
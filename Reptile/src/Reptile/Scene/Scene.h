#pragma once

#include <entt.hpp>
#include "Reptile/Core/Timestep.h"

namespace Reptile {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}
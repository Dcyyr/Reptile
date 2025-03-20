#pragma once

#include <entt.hpp>
#include "Reptile/Core/Timestep.h"

namespace Reptile {
	class Entity;

<<<<<<< HEAD
	class Entity;

=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
		friend class Entity;
	};
}
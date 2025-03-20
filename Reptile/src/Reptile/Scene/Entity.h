#pragma once
<<<<<<< HEAD
<<<<<<< HEAD
#include <entt.hpp>

#include "Scene.h"

namespace Reptile {
=======
=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb

#include "Scene.h"
#include "entt.hpp"

namespace Reptile{
<<<<<<< HEAD
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			RP_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			RP_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}
<<<<<<< HEAD
<<<<<<< HEAD

=======
		
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
=======
		
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
		template<typename T>
		void RemoveComponent()
		{
			RP_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
<<<<<<< HEAD
<<<<<<< HEAD
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
=======
=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb

			return m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
		
		operator bool() const { return m_EntityHandle != entt::null; }

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;

	};

<<<<<<< HEAD
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
}
#include "rppch.h"
#include "Entity.h"

namespace Reptile {

	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle),m_Scene(scene)
	{

	}
}
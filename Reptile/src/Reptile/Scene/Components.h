#pragma once

#include <glm/glm.hpp>
<<<<<<< HEAD
#include "Reptile/Renderer/Camera.h"
=======

>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb

namespace Reptile {
	
	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {}
	};

<<<<<<< HEAD
	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag){}
	};


=======
>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
	struct TransformComponent
	{
		glm::mat4 Transform{1.0f};

		TransformComponent() = default;//默认
		TransformComponent(const TransformComponent&) = default;//拷贝构造函数
		TransformComponent(const glm::mat4& transform)
			:Transform(transform){}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& ()const { return Transform; }
		
	};

	 
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f,1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			:Color(color){}
	};

<<<<<<< HEAD
<<<<<<< HEAD
	struct CameraComponent
	{
		Camera Camera;
		bool Primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projection)
			:Camera(projection) {
		}
	};

	
=======

>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
=======

>>>>>>> 5300d42041628bc510293625d8adff7ce28217eb
}


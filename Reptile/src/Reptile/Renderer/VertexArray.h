#pragma once

#include<memory>
#include"Reptile/Renderer/Buffer.h"

namespace Reptile {

	class VertexArray
	{
	public:
		virtual ~VertexArray(){}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Reptile::Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Reptile::Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Reptile::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Reptile::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

	};
}
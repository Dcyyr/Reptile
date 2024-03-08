#pragma once

#include"Reptile/Renderer/VertexArray.h"

namespace Reptile {


	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Reptile::Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Reptile::Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Reptile::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Reptile::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<Reptile::Ref<VertexBuffer>> m_VertexBuffers;
		Reptile::Ref<IndexBuffer> m_IndexBuffer;
	};
}
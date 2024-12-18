#include "rppch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Reptile {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Reptile::ShaderDataType::Float:    return GL_FLOAT;
		case Reptile::ShaderDataType::Float2:   return GL_FLOAT;
		case Reptile::ShaderDataType::Float3:   return GL_FLOAT;
		case Reptile::ShaderDataType::Float4:   return GL_FLOAT;
		case Reptile::ShaderDataType::Mat3:     return GL_FLOAT;
		case Reptile::ShaderDataType::Mat4:     return GL_FLOAT;
		case Reptile::ShaderDataType::Int:      return GL_INT;
		case Reptile::ShaderDataType::Int2:     return GL_INT;
		case Reptile::ShaderDataType::Int3:     return GL_INT;
		case Reptile::ShaderDataType::Int4:     return GL_INT;
		case Reptile::ShaderDataType::Bool:     return GL_BOOL;
		}

		RP_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		RP_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		RP_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		RP_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		RP_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		RP_PROFILE_FUNCTION();
		RP_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		RP_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
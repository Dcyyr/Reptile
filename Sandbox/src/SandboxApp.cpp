#include"Reptile.h"

#include"Platform/OpenGL/OpenGLShader.h"
#include"imgui/imgui.h"
#include<glm/gtc/matrix_transform.hpp>


#include<glm/gtc/type_ptr.hpp>

class ExampleLayer : public Reptile::Layer
{
public:
	ExampleLayer() 
		:Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Reptile::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f,-0.5f,0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f, 0.5f,0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Reptile::Ref<Reptile::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Reptile::VertexBuffer::Create(vertices, sizeof(vertices)));

		Reptile::BufferLayout layout = {
			{Reptile::ShaderDataType::Float3,"a_Position"},
			{Reptile::ShaderDataType::Float4,"a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0,1,2 };
		Reptile::Ref<Reptile::IndexBuffer> indexBuffer;
		indexBuffer.reset(Reptile::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Reptile::VertexArray::Create());

		float squareVerices[3 * 4] = {
			-0.75f,-0.75f,0.0f,
			 0.75f,-0.75f,0.0f,
			 0.75f, 0.75f,0.0f,
			-0.75f, 0.75f,0.0f
		};

		Reptile::Ref<Reptile::VertexBuffer> squareVB;
		squareVB.reset(Reptile::VertexBuffer::Create(squareVerices, sizeof(squareVerices)));
		squareVB->SetLayout({
			{Reptile::ShaderDataType::Float3,"a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Reptile::Ref<Reptile::IndexBuffer> squareIB;
		squareIB.reset(Reptile::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;
				
				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{ 
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);

				}

		)";

		std::string fragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;
					

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position*0.5+0.5, 1.0);
					color = v_Color;

				}

		)";

		m_Shader.reset(Reptile::Shader::Create(vertexSrc, fragmentSrc));


		std::string flatShaderVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				
				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;
				out vec3 v_Position;
				

				void main()
				{
					v_Position = a_Position;
					gl_Position =u_ViewProjection * u_Transform * vec4(a_Position,1.0);

				}

		)";

		std::string flatShaderFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;
				
				in vec3 v_Position;
				
				uniform vec3 u_Color;
				void main()
				{
					color = vec4(u_Color, 1.0);

				}
			
		)";
		m_FlatColorShader.reset(Reptile::Shader::Create(flatShaderVertexSrc, flatShaderFragmentSrc));

	}

	

	void OnUpdate(Reptile::Timestep ts) override
	{
		if (Reptile::Input::IsKeyPressed(RP_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Reptile::Input::IsKeyPressed(RP_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Reptile::Input::IsKeyPressed(RP_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Reptile::Input::IsKeyPressed(RP_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Reptile::Input::IsKeyPressed(RP_KEY_A))
			m_CameraRotaion += m_CameraRotaionSpeed * ts;
		else if (Reptile::Input::IsKeyPressed(RP_KEY_D))
			m_CameraRotaion -= m_CameraRotaionSpeed * ts;

		Reptile::RendererCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		Reptile::RendererCommand::Clear();


		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotaion);

		Reptile::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

		std::dynamic_pointer_cast<Reptile::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Reptile::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color",m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Reptile::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			
			}
		}
		Reptile::Renderer::Submit(m_Shader, m_VertexArray);	

		Reptile::Renderer::EndScene();
	}


	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Color Setting");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void OnEvent(Reptile::Event& event) override
	{
	}

private:
		Reptile::Ref<Reptile::Shader> m_Shader;
		Reptile::Ref<Reptile::VertexArray> m_VertexArray;

		Reptile::Ref<Reptile::VertexArray> m_SquareVA;
		Reptile::Ref<Reptile::Shader> m_FlatColorShader;
		Reptile::OrthographicsCamera m_Camera;

		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 3.0f;

		float m_CameraRotaion = 0.0f;
		float m_CameraRotaionSpeed = 60.0f;

		glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};

class Sandbox :public Reptile::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new Reptile::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Reptile::Application* Reptile::CreateApplication()
{
	return new Sandbox();

}
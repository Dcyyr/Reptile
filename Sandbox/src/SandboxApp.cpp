#include"Reptile.h"

#include"imgui/imgui.h"

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

		std::shared_ptr<Reptile::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Reptile::VertexBuffer::Create(vertices, sizeof(vertices)));

		Reptile::BufferLayout layout = {
			{Reptile::ShaderDataType::Float3,"a_Position"},
			{Reptile::ShaderDataType::Float4,"a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Reptile::IndexBuffer> indexBuffer;
		indexBuffer.reset(Reptile::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Reptile::VertexArray::Create());

		float squareVerices[3 * 4] = {
			-0.75f,-0.75f,0.0f,
			 0.75f,-0.75f,0.0f,
			 0.75f, 0.75f,0.0f,
			-0.75f, 0.75f,0.0f
		};

		std::shared_ptr<Reptile::VertexBuffer> squareVB;
		squareVB.reset(Reptile::VertexBuffer::Create(squareVerices, sizeof(squareVerices)));
		squareVB->SetLayout({
			{Reptile::ShaderDataType::Float3,"a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Reptile::IndexBuffer> squareIB;
		squareIB.reset(Reptile::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;
				
				uniform mat4 u_ViewProjection;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{ 
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * vec4(a_Position,1.0);

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

		m_Shader.reset(new Reptile::Shader(vertexSrc, fragmentSrc));


		std::string blueShaderVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				
				uniform mat4 u_ViewProjection;

				out vec3 v_Position;
				

				void main()
				{
					v_Position = a_Position;
					gl_Position =u_ViewProjection * vec4(a_Position,1.0);

				}

		)";

		std::string blueShaderFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;
				
				in vec3 v_Position;
				

				void main()
				{
					color = vec4(v_Position*0.5+0.5, 1.0);

				}
			
		)";
		m_BlueShader.reset(new Reptile::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}

	void OnUpdate() override
	{
		if (Reptile::Input::IsKeyPressed(RP_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Reptile::Input::IsKeyPressed(RP_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Reptile::Input::IsKeyPressed(RP_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (Reptile::Input::IsKeyPressed(RP_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Reptile::Input::IsKeyPressed(RP_KEY_A))
			m_CameraRotaion += m_CameraRotaionSpeed;
		else if (Reptile::Input::IsKeyPressed(RP_KEY_D))
			m_CameraRotaion -= m_CameraRotaionSpeed;

		Reptile::RendererCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		Reptile::RendererCommand::Clear();


		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotaion);

		Reptile::Renderer::BeginScene(m_Camera);

		Reptile::Renderer::Submit(m_BlueShader, m_SquareVA);
		Reptile::Renderer::Submit(m_Shader, m_VertexArray);

		Reptile::Renderer::EndScene();
	}

	void OnEvent(Reptile::Event& event) override
	{
	}

private:
		std::shared_ptr<Reptile::Shader> m_Shader;
		std::shared_ptr<Reptile::VertexArray> m_VertexArray;

		std::shared_ptr<Reptile::Shader> m_BlueShader;
		std::shared_ptr<Reptile::VertexArray> m_SquareVA;

		Reptile::OrthographicsCamera m_Camera;

		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 0.05f;

		float m_CameraRotaion = 0.0f;
		float m_CameraRotaionSpeed = 15.0f;
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
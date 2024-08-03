#include"Sandbox2D.h"
#include"imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),m_CameraController(1600.0f/900.0f)
{

}

void Sandbox2D::OnAttach()
{
	RP_PROFILE_FUNCTION();
	m_CheckboardTexture = Reptile::Texture2D::Create("assets/textures/1.png");
}

void Sandbox2D::OnDetach()
{
	RP_PROFILE_FUNCTION();

}

void Sandbox2D::OnEvent(Reptile::Event& e)
{
	
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnUpdate(Reptile::Timestep ts)
{
	// Update
		RP_PROFILE_FUNCTION();
		m_CameraController.OnUpdate(ts);

	Reptile::Renderer2D::ResetStats();
	{
		RP_PROFILE_SCOPE("Renderer Prep");
		Reptile::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Reptile::RendererCommand::Clear();
	}
	// Render
	{
		static float rotation = 0.0f;
		rotation += ts*50.0f;

		RP_PROFILE_SCOPE("Renderer Draw");
		Reptile::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Reptile::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Reptile::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Reptile::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Reptile::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckboardTexture, 10.0f);
		Reptile::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckboardTexture, 10.0f);
		Reptile::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckboardTexture, 20.0f);
		Reptile::Renderer2D::EndScene();

		Reptile::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0 / 10.0),0.4f,(y + 5.0f) / 10.0f,0.5f };
				Reptile::Renderer2D::DrawQuad({ x,y }, { 0.45f,0.45f }, color);
			}
		}

		Reptile::Renderer2D::EndScene();


		//Reptile::Renderer2D::DrawRotatedQuad({ 0.0f,0.0f,-0.1f }, { 10.0f,10.0f }, glm::radians(80.0f),m_CheckboardTexture, 10.0f, glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	auto stats = Reptile::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("DrawCalls: %d", stats.DrawCalls);
	ImGui::Text("Quad: %d", stats.QuadCount);
	ImGui::Text("Vertics: %d", stats.GetVertexCount());
	ImGui::Text("indices: %d", stats.GetIndexCount());

	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}




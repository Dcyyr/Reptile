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

	{
		RP_PROFILE_SCOPE("Renderer Prep");
		Reptile::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Reptile::RendererCommand::Clear();
	}
	// Render
	{
		RP_PROFILE_SCOPE("Renderer Draw");
		Reptile::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Reptile::Renderer2D::DrawRotatedQuad({ -1.0f,0.0f }, { 0.5f,0.8f },glm::radians(-45.0f), { 0.9f,0.4f,0.3f,1.0f });
		Reptile::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 1.0f,1.0f }, { 0.8f,0.2f,0.3f,1.0f });
		Reptile::Renderer2D::DrawRotatedQuad({ 0.0f,0.0f,-0.1f }, { 10.0f,10.0f }, glm::radians(80.0f),m_CheckboardTexture, 10.0f, glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));
	}
	Reptile::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	
	ImGui::End();
}




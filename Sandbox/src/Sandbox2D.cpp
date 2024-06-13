#include"Sandbox2D.h"
#include"imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),m_CameraController(1600.0f/900.0f)
{

}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnEvent(Reptile::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnUpdate(Reptile::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);
	Reptile::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Reptile::RendererCommand::Clear();
	// Render
	Reptile::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Reptile::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, { 0.8f,0.2f,0.3f,1.0f });
	Reptile::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}




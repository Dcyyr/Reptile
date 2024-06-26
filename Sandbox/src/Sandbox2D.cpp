#include"Sandbox2D.h"
#include"imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name,Fn&& func)
		:m_Name(name),m_Func(func),m_Stopped(false)

	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto EndTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name,duration });
	}
private:
	const char* m_Name;
	bool m_Stopped;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name,[&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult);})

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),m_CameraController(1600.0f/900.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckboardTexture = Reptile::Texture2D::Create("assets/textures/1.png");
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
	{
		PROFILE_SCOPE("Sandbox::OnUpdata");
		m_CameraController.OnUpdate(ts);

	}
	{
		PROFILE_SCOPE("Renderer Prep");
		Reptile::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Reptile::RendererCommand::Clear();
	}
	// Render
	{
		PROFILE_SCOPE("Renderer Draw");
		Reptile::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Reptile::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.5f,0.8f }, { 0.9f,0.4f,0.3f,1.0f });
		Reptile::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 1.0f,1.0f }, { 0.8f,0.2f,0.3f,1.0f });
		Reptile::Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 10.0f,10.0f }, m_CheckboardTexture);
	}
	Reptile::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, " %.3fms");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();
	ImGui::End();
}




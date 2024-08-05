#pragma once

#include"Reptile.h"

class Sandbox2D :public Reptile::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Reptile::Timestep ts)override;
	void OnEvent(Reptile::Event& e)override;
	virtual void OnImGuiRender()override;
private:
	Reptile::OrthographicCameraController m_CameraController;

	Reptile::Ref<Reptile::VertexArray>m_SquareVA;
	Reptile::Ref<Reptile::Shader> m_FlatColorShader;
	Reptile::Ref<Reptile::Texture2D> m_CheckboardTexture;
	Reptile::Ref<Reptile::Framebuffer> m_Framebuffer;

	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };

};
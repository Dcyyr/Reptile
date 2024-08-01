#pragma once

#include "Reptile.h"

class ExampleLayer :public Reptile::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Reptile::Timestep ts) override;
	virtual void OnImGuiRender() override;

	void OnEvent(Reptile::Event& e) override;

private:
	Reptile::ShaderLibrary m_ShaderLibrary;
	Reptile::Ref<Reptile::Shader> m_Shader;
	Reptile::Ref<Reptile::VertexArray> m_VertexArray;

	Reptile::Ref<Reptile::Shader> m_FlatColorShader;
	Reptile::Ref<Reptile::VertexArray> m_SquareVA;

	Reptile::Ref<Reptile::Texture2D> m_Texture, m_ChernoLogoTexture;

	Reptile::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

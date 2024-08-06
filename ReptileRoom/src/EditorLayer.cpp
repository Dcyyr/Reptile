#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Reptile {

    EditorLayer::EditorLayer()
        :Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f)
    {

    }

    void EditorLayer::OnAttach()
    {
        RP_PROFILE_FUNCTION();
        m_CheckboardTexture = Texture2D::Create("assets/textures/1.png");

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbSpec);

    }

    void EditorLayer::OnDetach()
    {
        RP_PROFILE_FUNCTION();

    }

    void EditorLayer::OnEvent(Event& e)
    {

        m_CameraController.OnEvent(e);
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        // Update
        RP_PROFILE_FUNCTION();
        m_CameraController.OnUpdate(ts);

        Renderer2D::ResetStats();
        {
            RP_PROFILE_SCOPE("Renderer Prep");
            m_Framebuffer->Bind();
            RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RendererCommand::Clear();
        }
        // Render
        {
            static float rotation = 0.0f;
            rotation += ts * 50.0f;

            RP_PROFILE_SCOPE("Renderer Draw");
            Renderer2D::BeginScene(m_CameraController.GetCamera());
            Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
            Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
            Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
            Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckboardTexture, 10.0f);
            Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckboardTexture, 10.0f);
            Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckboardTexture, 20.0f);
            Renderer2D::EndScene();

            Renderer2D::BeginScene(m_CameraController.GetCamera());
            for (float y = -5.0f; y < 5.0f; y += 0.5f)
            {

                for (float x = -5.0f; x < 5.0f; x += 0.5f)
                {
                    glm::vec4 color = { (x + 5.0 / 10.0),0.4f,(y + 5.0f) / 10.0f,0.5f };
                    Renderer2D::DrawQuad({ x,y }, { 0.45f,0.45f }, color);
                }
            }

            Renderer2D::EndScene();

            m_Framebuffer->Unbind();
            // Renderer2D::DrawRotatedQuad({ 0.0f,0.0f,-0.1f }, { 10.0f,10.0f }, glm::radians(80.0f),m_CheckboardTexture, 10.0f, glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));
        }
    }

    void EditorLayer::OnImGuiRender()
    {

        static bool opt_fullscreen = true;
        static bool dockspace = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspace, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.


                if (ImGui::MenuItem("Close"))  Application::Get().Close();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
            ImGui::Begin("Settings");

            auto stats = Renderer2D::GetStats();
            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetVertexCount());
            ImGui::Text("Indices: %d", stats.GetIndexCount());

            static bool show = true;
            ImGui::ShowDemoWindow(&show);
            ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

            uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
            ImGui::Image((void*)textureID, ImVec2{ 1280,720 });
            ImGui::End();

            ImGui::End();
        }
        else
        {
            ImGui::Begin("Settings");

            auto stats = Renderer2D::GetStats();
            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetVertexCount());
            ImGui::Text("Indices: %d", stats.GetIndexCount());



            ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

            uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
            ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
            ImGui::End();
        }

    }

}


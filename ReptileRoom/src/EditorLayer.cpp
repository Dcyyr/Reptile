#include "Reptile.h"
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

        m_ActiveScene = std::make_shared<Scene>();
        //Entity
        auto square = m_ActiveScene->CreateEntity("Green Square");
        square.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        m_SquareEntity = square;

    }

    void EditorLayer::OnDetach()
    {
        RP_PROFILE_FUNCTION();

    }


    void EditorLayer::OnUpdate(Timestep ts)
    {
        // Update
        RP_PROFILE_FUNCTION();

        //Resize
        if (Reptile::FramebufferSpecification spec = m_Framebuffer->GetSpecification();
            m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_CameraController.OnResize((float)m_ViewportSize.x, (float)m_ViewportSize.y);
        }


        if(m_ViewportFocused)
            m_CameraController.OnUpdate(ts);

            Renderer2D::ResetStats();
        
            m_Framebuffer->Bind();
            RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RendererCommand::Clear();
        
        // Render

            Renderer2D::BeginScene(m_CameraController.GetCamera());
            m_ActiveScene->OnUpdate(ts);

            Renderer2D::EndScene();

      
      
            m_Framebuffer->Unbind();
            // Renderer2D::DrawRotatedQuad({ 0.0f,0.0f,-0.1f }, { 10.0f,10.0f }, glm::radians(80.0f),m_CheckboardTexture, 10.0f, glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));
        
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
        }
            ImGui::Begin("Settings");

            auto stats = Renderer2D::GetStats();
            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetVertexCount());
            ImGui::Text("Indices: %d", stats.GetIndexCount());

            {
                ImGui::Separator();
                auto& tag = m_SquareEntity.GetComponent<TagComponent>().Tag;
                ImGui::Text("%s", tag.c_str());

                auto& SquareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
                ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));
                ImGui::Separator();
            }
            
            ImGui::End();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
            ImGui::Begin("Viewport");
            m_ViewportFocused = ImGui::IsWindowFocused();
            m_ViewportHovered = ImGui::IsWindowHovered();
            Application::Get().GetImGuiLayer()->BlockEvent(!m_ViewportFocused || !m_ViewportHovered);

            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
           
            m_ViewportSize = { viewportPanelSize.x,viewportPanelSize.y };

            uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
            ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y },ImVec2{0,1},ImVec2{1,0});
            ImGui::End();
            ImGui::PopStyleVar();

            ImGui::End();
        }
    
        void EditorLayer::OnEvent(Event& e)
        {

            m_CameraController.OnEvent(e);
        }

}




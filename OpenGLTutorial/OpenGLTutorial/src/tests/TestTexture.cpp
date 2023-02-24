#include "TestTexture.h"

#include "Renderer.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Tests {

    TestTexture::TestTexture()
        : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_TranslationA(200, 200, 0), m_TranslationB(400, 400, 0) {

        /* Coords of vertices */
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f
        };

        /* Specify indices of positions that GPU should use */
        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        /* Blending of transparent/partially transparent textures */
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_VAO = std::make_unique<VertexArray>();



        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        m_Layout = std::make_unique<VertexBufferLayout>();
        m_Layout->Push<float>(2);
        m_Layout->Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, *m_Layout);

        m_IB = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        m_Texture = std::make_unique<Texture>("res/textures/potato.jpg");
        //m_Texture = std::make_unique<Texture>("res/textures/gooseKnife.png");

        m_Shader->SetUniform1i("u_Texture", 0);
    }

    TestTexture::~TestTexture() {
    }

    void TestTexture::OnUpdate(float deltaTime) {
    }

    void TestTexture::OnRender() {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IB, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IB, *m_Shader);
        }
    }

    void TestTexture::OnImGuiRender() {
        ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 540.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
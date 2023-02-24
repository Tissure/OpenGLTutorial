#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

Tests::TestClearColor::TestClearColor() : m_ClearColor{ 0.2f, 0.3f,0.5f, 1.0f } {
}

Tests::TestClearColor::~TestClearColor() {
}

void Tests::TestClearColor::OnUpdate(float deltaTime) {
}

void Tests::TestClearColor::OnRender() {
    GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Tests::TestClearColor::OnImGuiRender() {
    ImGui::ColorEdit4("Clear Color", m_ClearColor);
}

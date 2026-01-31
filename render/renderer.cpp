#include "renderer.hpp"

void Renderer::renderScene(Scene& scene) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    if (GEngine().activeCamera != nullptr) {
        view = GEngine().activeCamera->m_viewMatrix;
        projection = GEngine().activeCamera->m_projectionMatrix;
    }

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    for (const auto& obj : scene.getAllObjects()) {
        if (!obj->metaData.isVisible) continue;

        obj->Bind();

        updateMatrixUniforms(obj->m_transform);

        obj->Draw();
    }
}

void Renderer::updateMatrixUniforms(const glm::mat4& model) {
    shader.setMat4("model", model);
}

void Renderer::setShaderpaths(Shader_class& shader, const char* vertexPath, const char* fragmentPath) {
    shader = Shader_class(vertexPath, fragmentPath);
}

void Renderer::useShader() {
    shader.use();
}
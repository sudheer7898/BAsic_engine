#include "renderer.hpp"

void Renderer::renderScene(Scene& scene) {
    // 1. Prepare Fallback Matrices
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // 2. Extract Camera Data if available
    if (GEngine().activeCamera != nullptr) {
        view = GEngine().activeCamera->m_viewMatrix;
        projection = GEngine().activeCamera->m_projectionMatrix;
    }

    // 3. UPLOAD GLOBAL UNIFORMS (Do this BEFORE the loop)
    // This ensures every object in the loop uses the same camera perspective
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // 4. Draw the objects
    for (const auto& obj : scene.getAllObjects()) {
        if (!obj->metaData.isVisible) continue;

        // Binds VAO and Texture (if it exists)
        obj->Bind();

        // Upload the object's specific model matrix
        updateMatrixUniforms(obj->m_transform);

        // Final draw call for this object
        obj->Draw();
    }
}

void Renderer::updateMatrixUniforms(const glm::mat4& model) {
    shader.setMat4("model", model);
}

void Renderer::setShaderpaths(Shader_class& shader, const char* vertexPath, const char* fragmentPath) {
    // Reinitialize shader with new paths
    shader = Shader_class(vertexPath, fragmentPath);
}

void Renderer::useShader() {
    shader.use();
}
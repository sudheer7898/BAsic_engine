#include "renderer.hpp"

void Renderer::renderScene(Scene& scene) {
	for (const auto& obj : scene.getAllObjects()) {
		if (!obj->metaData.isVisible) {
			continue;
		}
		obj->Bind();
		updateMatrixUniforms(obj->m_transform);
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

void Renderer::useShader(){
	shader.use();
}

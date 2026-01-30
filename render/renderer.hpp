#pragma once
#include"../engine_state.hpp"
#include "../scene/scene.hpp"
#include "../shader/Shader_class.hpp"


class Renderer {
public:
	Renderer() = default;
	void renderScene(Scene& scene = *GEngine().activeScene);

	void updateMatrixUniforms(const glm::mat4& model);

	void setShaderpaths(Shader_class& shader, const char* vertexPath, const char* fragmentPath);

	void useShader();

	void returnPtrShader(std::shared_ptr<Shader_class>& outShader) {
		outShader = std::make_shared<Shader_class>(shader);
	}

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Shader_class shader;
};
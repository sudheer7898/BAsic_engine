#pragma once
#include"../engine_state.hpp"
#include "../scene/scene.hpp"
#include "../shader/Shader_class.hpp"

class Renderer {
public:
	Renderer() = default;
	void renderScene(Scene& scene=*GEngine().activeScene);

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
};
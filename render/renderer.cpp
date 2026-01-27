#include "renderer.hpp"

void Renderer::renderScene(Scene& scene){
	for(std::shared_ptr<GameObject> obj : scene.getAllObjects()){
		if(!obj->metaData.isVisible){
			continue;
		}
		obj->Bind();
		obj->Draw();
	}
}


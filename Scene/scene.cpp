#include"scene.hpp"
#include"../engine_state.hpp"

void Scene::addObject(std::shared_ptr<GameObject> object) {
	m_scene.push_back(object);
}

int Scene::searchObjectByID(uint32_t id) {
	for (int i = 0; i < m_scene.size(); i++) {
		if (m_scene[i]->getID() == id) {
			return i;
		}
	}
	return -1;
}

int Scene::searchObjectByName(const std::string& name)
{
	for (int i = 0; i < m_scene.size(); i++) {
		if (m_scene[i]->m_name == name) {
			return i;
		}
	}
	return -1;
}

void Scene::removeObject(uint32_t id) {
	for (auto it = m_scene.begin(); it != m_scene.end(); ++it) {
		if ((*it)->getID() == id) {
			m_scene.erase(it);
			break;
		}
	}
}

void Scene::removeObject(const std::string& name) {
	for (auto it = m_scene.begin(); it != m_scene.end(); ++it) {
		if ((*it)->m_name == name) {
			m_scene.erase(it);
			break;
		}
	}
}

std::vector<std::shared_ptr<GameObject>> Scene::getAllObjects() const { return m_scene; }

void Scene::ClearScene() {
	deleteScene();
}

void Scene::deleteScene() {
	m_scene.clear();
}

void Scene::ActivateScene() { metaData.isActive = true; GEngine().activeScene = this; }
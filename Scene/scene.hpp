#pragma once
#include"../Objects/gameObject.hpp"
class Scene {
public:
	Scene(std::string name){
		m_name = name;
	}
	std::string m_name;

	void addObject(std::shared_ptr<GameObject> object);
	
	int searchObjectByID(uint32_t id);

	int searchObjectByName(const std::string& name);

	void removeObject(uint32_t id);

	void removeObject(const std::string& name);

	std::vector<std::shared_ptr<GameObject>> getAllObjects() const;

	std::string getName() const { return m_name; }

	struct MetaData {
		bool isActive = true;
	}metaData;

	int getSize() const { return static_cast<int>(m_scene.size()); }

	void ClearScene();

	void deleteScene();
	void ActivateScene();
private:
	std::vector<std::shared_ptr<GameObject>> m_scene;
};
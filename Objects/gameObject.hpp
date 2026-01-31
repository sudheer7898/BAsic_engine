#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <string>
#include <memory>
#include <vector>

class Texture_2D;

enum class DrawMode {
	POINTS,
	LINES,
	LINE_STRIP,
	TRIANGLES,
	TRIANGLE_STRIP
};

enum class Layout {
	POSITION,
	COLOR,
	TEXCOORD
};

class GameObject {
public:
	GameObject() = default;
	static std::shared_ptr<GameObject> Create(const std::string& name) {
		static uint32_t id_counter = 1;
		auto obj = std::shared_ptr<GameObject>(new GameObject(name, id_counter++));
		return obj;
	}
	std::shared_ptr<Texture_2D> m_texture = nullptr;
	std::string m_name;
	std::vector<std::string>tags;
	glm::mat4 m_transform = glm::mat4(1.0f);
	uint32_t m_id = 0;
	struct MetaData {
		bool isVisible = true;
		bool isStatic = false;
	}metaData;

	void setTags(std::string tag);

	bool SearchTag(std::string tag) const;

	void setLayout(Layout layout, int num);

	void setMeshData(const std::vector<float>& positions, const std::vector<float>& colors);

	void setMeshData(const std::vector<float>& positions,const std::vector<float>& color,const std::vector<float>& texCoords);

	void Draw() const;

	void setDrawMode(DrawMode mode);

	uint32_t getID() const { return m_id; }

	~GameObject();

	std::vector<float> getInterLeavedData() const { return interLeaved_data; }

	void Bind();

	void translate(float axis[3]);

	void rotate(float angle, float axis[3]);

	void scale(float axis[3]);

	void setTexture(const std::string& texturePath);

	std::shared_ptr<GameObject> m_parent = nullptr;
private:
	GameObject(const std::string& name, const uint32_t m_id = 0) : m_name(name), m_id(m_id), vertexCount(0) {
		setUpGPUBuffer();
	}
	std::vector<float> interLeaved_data = {};
	size_t vertexCount = 0;
	void setUpGPUBuffer(); // Placeholder for GPU buffer setup
	unsigned int m_VBO = 0, m_VAO = 0; // OpenGL Buffer Objects
	int m_posAttributeLocation = 0;
	int m_colorAttributeLocation = 1;
	int m_texCoordAttributeLocation = 2;
	DrawMode m_drawMode = DrawMode::TRIANGLES;
};
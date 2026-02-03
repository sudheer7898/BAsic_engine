#include<glm/glm.hpp>
#include<vector>
#include<string>
#include<memory>

class Mesh {
public:
	static std::shared_ptr<Mesh> Create(std::string& name) { 
		auto mesh = std::make_shared<Mesh>();
		mesh->mesh_name = name;
		mesh->setupMesh();
		return mesh;
	};
	glm::mat4 m_localTransform = glm::mat4(1.0f);
	void setMeshdata(const std::vector<float>& positions);
	void setMeshId(unsigned int id) { set_id = id; }
	std::string mesh_name;
	void setPositionAttributeLocation(int location);
	void setStride(int stride);
	void bind()const;
	std::vector<float>& getInterLeavedData() { return interLeaved_data; }
private:
	std::vector<float> interLeaved_data;
	int m_stride = 3;
	unsigned int VAO=0, VBO=0, EBO=0;
	int m_posAttributeLocation = 0;
	size_t vertexCount = 0;
	uint32_t set_id = 0;
	void setupMesh();
};
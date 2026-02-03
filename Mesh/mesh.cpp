#include "mesh.hpp"
#include<glad/glad.h>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>

void Mesh::setMeshdata(const std::vector<float>& positions){
	if (positions.empty()) {
		std::cout << "Empty positions data for mesh id: " << set_id << std::endl;
		return;
	}
	vertexCount = positions.size() / 3;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(m_posAttributeLocation, 3, GL_FLOAT, GL_FALSE, m_stride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_posAttributeLocation);
}

void Mesh::setPositionAttributeLocation(int location) { m_posAttributeLocation = location; }

void Mesh::setStride(int stride){
	m_stride = stride;
}

void Mesh::bind() const{
	glBindVertexArray(VAO);
}

void Mesh::setupMesh(){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}
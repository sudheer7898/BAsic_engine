#include"gameObject.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
void GameObject::setTags(std::string tag) {
	tags.push_back(tag);
}

bool GameObject::SearchTag(std::string tag) const {
	if (tags.empty()) {
		std::cout << "The given object has no tags assigned to it." << std::endl;
		return false;
	}
	for (auto& t : tags) {
		if (t == tag) {
			return true;
		}
	}
	return false;
}

void GameObject::setLayout(Layout layout, int num) {
	switch (layout)
	{
	case Layout::POSITION:m_posAttributeLocation = num;
		break;
	case Layout::COLOR:
		m_colorAttributeLocation = num;
		break;
	default:
		break;
	}
}

void GameObject::setMeshData(const std::vector<float>& positions, const std::vector<float>& colors) {
	if (positions.size() != colors.size()) {
		std::cout << "Positions and colors size mismatch for object: " << m_name << std::endl;
		return;
	}
	if (positions.empty() || colors.empty()) {
		std::cout << "Empty positions or colors data for object: " << m_name << std::endl;
		return;
	}
	interLeaved_data.clear();
	vertexCount = positions.size() / 3;
	for (size_t i = 0; i < vertexCount; ++i) {
		interLeaved_data.push_back(positions[i * 3]);     // x
		interLeaved_data.push_back(positions[i * 3 + 1]); // y
		interLeaved_data.push_back(positions[i * 3 + 2]); // z
		interLeaved_data.push_back(colors[i * 3]);        // r
		interLeaved_data.push_back(colors[i * 3 + 1]);    // g
		interLeaved_data.push_back(colors[i * 3 + 2]);    // b
	}
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, interLeaved_data.size() * sizeof(float), interLeaved_data.data(), GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(m_posAttributeLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_posAttributeLocation);
	// Color attribute
	glVertexAttribPointer(m_colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_colorAttributeLocation);

}

void GameObject::Draw() const {
	if (vertexCount == 0) {
		std::cout << "No vertex data to draw for object: " << m_name << std::endl;
		return;
	}
	switch (m_drawMode) {
	case DrawMode::POINTS:
		glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(vertexCount));
		break;
	case DrawMode::LINES:
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vertexCount));
		break;
	case DrawMode::LINE_STRIP:
		glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(vertexCount));
		break;
	case DrawMode::TRIANGLES:
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
		break;
	case DrawMode::TRIANGLE_STRIP:
		glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(vertexCount));
		break;
	default:
		break;
	}
}
void GameObject::setDrawMode(DrawMode mode) { m_drawMode = mode; }

GameObject::~GameObject() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void GameObject::Bind() {
	glBindVertexArray(m_VAO);
}

void GameObject::setUpGPUBuffer() {
	if (m_VBO == 0) {
		glGenBuffers(1, &m_VBO);
	}
	if (m_VAO == 0) {
		glGenVertexArrays(1, &m_VAO);
	}
}

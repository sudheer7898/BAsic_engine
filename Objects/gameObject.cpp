#include"gameObject.hpp"
#include"../Texture/texture.hpp"
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
	case Layout::TEXCOORD:
		m_texCoordAttributeLocation = num;
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

void GameObject::setMeshData(const std::vector<float>& positions, const std::vector<float>& color, const std::vector<float>& texCoords){
	if(vertexCount==0){
		if (positions.size()/3 != color.size()/3 || positions.size()/3 != texCoords.size()/2) {
			std::cout << "Positions, colors and texCoords size mismatch for object: " << m_name << std::endl;
			return;
		}
		if (positions.empty() || color.empty() || texCoords.empty()) {
			std::cout << "Empty positions, colors or texCoords data for object: " << m_name << std::endl;
			return;
		}
		vertexCount = positions.size() / 3;
		interLeaved_data.clear();
		for (size_t i = 0; i < vertexCount; ++i) {
			interLeaved_data.push_back(positions[i * 3]);     // x
			interLeaved_data.push_back(positions[i * 3 + 1]); // y
			interLeaved_data.push_back(positions[i * 3 + 2]); // z
			interLeaved_data.push_back(color[i * 3]);        // r
			interLeaved_data.push_back(color[i * 3 + 1]);    // g
			interLeaved_data.push_back(color[i * 3 + 2]);    // b
			interLeaved_data.push_back(texCoords[i * 2]);    // u
			interLeaved_data.push_back(texCoords[i * 2 + 1]); // v
		}
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, interLeaved_data.size() * sizeof(float), interLeaved_data.data(), GL_STATIC_DRAW);
		// Position attribute
		glVertexAttribPointer(m_posAttributeLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(m_posAttributeLocation);
		// Color attribute
		glVertexAttribPointer(m_colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(m_colorAttributeLocation);
		// TexCoord attribute
		glVertexAttribPointer(m_texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(m_texCoordAttributeLocation);
	}
	else {
		std::cout << "Mesh data has already been set for object: " << m_name << std::endl;
	}
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
	if(m_texture){
		m_texture->Bind();
	}
	glBindVertexArray(m_VAO);
}

void GameObject::translate(float axis[3]) {
	if (axis == nullptr) {
		std::cout << "the translate axis pointer is null." << std::endl;
		return;
	}
	glm::vec3 translateAxis = glm::vec3(axis[0], axis[1], axis[2]);
	//glm::mat4 trans = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, translateAxis);
}

void GameObject::rotate(float angle, float axis[3]) {
	if (axis == nullptr) {
		std::cout << "the rotate axis pointer is null." << std::endl;
		return;
	}
	glm::vec3 rotateAxis = glm::vec3(axis[0], axis[1], axis[2]);
	m_transform = glm::rotate(m_transform, glm::radians(angle), rotateAxis);
}

void GameObject::scale(float axis[3]) {
	if (axis == nullptr) {
		std::cout << "the scale axis pointer is null." << std::endl;
		return;
	}
	glm::vec3 scaleAxis = glm::vec3(axis[0], axis[1], axis[2]);
	m_transform = glm::scale(m_transform, scaleAxis);
}

void GameObject::setTexture(const std::string& texturePath){
	m_texture = std::make_shared<Texture_2D>(texturePath.c_str());
	m_texture->SetParameter(TextureParams::WRAP_S, TextureValues::REPEAT);
	m_texture->SetParameter(TextureParams::WRAP_T, TextureValues::REPEAT);
	m_texture->SetParameter(TextureParams::MIN_FILTER, TextureValues::LINEAR_MIPMAP_LINEAR);
	m_texture->SetParameter(TextureParams::MAG_FILTER, TextureValues::LINEAR);
}

void GameObject::setUpGPUBuffer() {
	if (m_VBO == 0) {
		glGenBuffers(1, &m_VBO);
	}
	if (m_VAO == 0) {
		glGenVertexArrays(1, &m_VAO);
	}
}
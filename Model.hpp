#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util.hpp"

#ifndef __MODEL_H__
#define __MODEL_H__
class Model{
public:
	GLuint vao, buffer;
	unsigned int numVertices;
	glm::vec3 m_scale = glm::vec3(0.02f);
	Model(int num_ver, point4* vertices, glm::vec3* normals,  GLuint vPosition, GLuint vNormal){
		numVertices = num_ver;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point4)*numVertices + sizeof(glm::vec3)*numVertices, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4)*numVertices, vertices);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4)*numVertices, sizeof(glm::vec3)*numVertices, normals);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vNormal);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4)*numVertices));
	}

	glm::mat4 getModelMatrix(float x, float y, float z){
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, glm::vec3(x, y, z));
		mat = glm::scale(mat, m_scale);
		return mat;
	}

	void setScale(float x, float y, float z){
		m_scale = glm::vec3(x, y, z);
	}

	void Bind(){
		GLCall(glBindVertexArray(vao));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	}
};


#endif

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

	Model(Data& data,  GLuint vPosition, GLuint vNormal);
	glm::mat4 getModelMatrix(float x, float y, float z);
	void setScale(float x, float y, float z);
	void Bind();
};


#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

#include "util.hpp"
#include "InitShader.hpp"

#ifndef __SHADER_H__
#define __SHADER_H__


class Shader{
public:
	GLuint m_program;
	std::unordered_map<std::string, GLint> m_uniforms;

	Shader();
	Shader(const std::string& vshader, const std::string& fshader);
	~Shader();
	GLint getUniformLocation(const std::string& name);
	GLint getAttribLocation(const std::string& name);
	void setUniformMat4(const std::string& name, glm::mat4& mat);
	void setUniform4f(const std::string& name, glm::vec4 vec);
	void setUniform1f(const std::string& name, float val);
	void Bind();
};
#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

#include "util.hpp"
#include "InitShader.hpp"
#include "Shader.hpp"


Shader::Shader(){
}

Shader::Shader(const std::string& vshader, const std::string& fshader){
	m_program = InitShader(vshader.c_str(), fshader.c_str());
}

Shader::~Shader(){
	GLCall(glDeleteShader(m_program));
}

GLint Shader::getUniformLocation(const std::string& name){
	GLint location;
	if(m_uniforms.find(name) == m_uniforms.end()){
		GLCall(location = glGetUniformLocation(m_program, name.c_str()));
		if(location == -1){
			std::cout << "Uniform: " << name << " Location not found" << std::endl;
		}
		m_uniforms[name] = location;
	}else{
		location = m_uniforms.at(name);
	}
	return location;
}

GLint Shader::getAttribLocation(const std::string& name){
	GLint location;
	GLCall(location = glGetAttribLocation(m_program, name.c_str()));
	return location;
}

void Shader::setUniformMat4(const std::string& name, glm::mat4& mat){
	GLint location = getUniformLocation(name);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat)));
}

void Shader::setUniform4f(const std::string& name, glm::vec4 vec){
	GLint location = getUniformLocation(name);
	GLCall(glUniform4fv(location, 1, glm::value_ptr(vec)));
}

void Shader::setUniform1f(const std::string& name, float val){
	GLint location = getUniformLocation(name);
	GLCall(glUniform1f(location, val));
}



void Shader::Bind(){
	GLCall(glUseProgram(m_program));
}


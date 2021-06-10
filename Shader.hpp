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

	Shader(){
	}

	Shader(const std::string& vshader, const std::string& fshader){
		m_program = InitShader(vshader.c_str(), fshader.c_str());
	}

	~Shader(){
		GLCall(glDeleteShader(m_program));
	}

	GLint getUniformLocation(const std::string& name){
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

	GLint getAttribLocation(const std::string& name){
		GLint location;
		GLCall(location = glGetAttribLocation(m_program, name.c_str()));
		return location;
	}

	void setUniformMat4(const std::string& name, glm::mat4& mat){
		GLint location = getUniformLocation(name);
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat)));
	}

	void setUniform4f(const std::string& name, glm::vec4 vec){
		GLint location = getUniformLocation(name);
		GLCall(glUniform4fv(location, 1, glm::value_ptr(vec)));
	}

	void setUniform1f(const std::string& name, float val){
		GLint location = getUniformLocation(name);
		GLCall(glUniform1f(location, val));
	}



	void Bind(){
		GLCall(glUseProgram(m_program));
	}
};

class ComputeShader : public Shader{
public:

	ComputeShader(){

	}

	ComputeShader(const std::string& file){
		compile(file);	
	}

	void compile(const std::string& file){
		char * source = readShaderSource(file.c_str());
		GLuint shader = glCreateShader(GL_COMPUTE_SHADER);			
		glShaderSource(shader, 1, (const GLchar**)&source, NULL);
		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if(!compiled){
			printf("Compute Not compiled\n");
			GLint  logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete [] logMsg;
			exit( EXIT_FAILURE );
		}

		m_program = glCreateProgram();
		glAttachShader(m_program, shader);
		glLinkProgram(m_program);

		GLint linked;
		glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
		if(!linked){
			printf("Compute not linked\n");
			GLint  logSize;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog(m_program, logSize, NULL, logMsg );
			std::cerr << logMsg << std::endl;
			delete [] logMsg;
			exit( EXIT_FAILURE );
		}

	}
};

#endif

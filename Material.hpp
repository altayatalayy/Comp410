//#pragma once
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Shader.hpp"


class Light{
public:
	glm::vec4 light_position = glm::vec4( 0.0, 0.0, 2.0, 0.0 );
	glm::vec4 light_ambient = glm::vec4( 0.2, 0.2, 0.2, 1.0 );
	glm::vec4 light_diffuse = glm::vec4( 1.0, 1.0, 1.0, 1.0 );
	glm::vec4 light_specular = glm::vec4( 1.0, 1.0, 1.0, 1.0 );

};

class Material {
public:
	
	glm::vec4 material_ambient = glm::vec4( 1.0, 0.0, 1.0, 1.0 );
	glm::vec4 material_diffuse = glm::vec4( 1.0, 0.8, 0.0, 1.0 );
	glm::vec4 material_specular = glm::vec4( 1.0, 0.0, 1.0, 1.0 );
	float material_shininess = 5.0;
	
	Light m_light;

	void useMaterial(Shader& shader){
		glm::vec4 ambient_product = m_light.light_ambient * material_ambient;
		glm::vec4 diffuse_product = m_light.light_diffuse * material_diffuse;
		glm::vec4 specular_product = m_light.light_specular * material_specular;

		shader.setUniform4f("LightPosition", m_light.light_position);
		shader.setUniform4f("AmbientProduct", ambient_product);
		shader.setUniform4f("DiffuseProduct", diffuse_product);
		shader.setUniform4f("SpecularProduct", specular_product);
		shader.setUniform1f("Shininess", material_shininess);
	}

	
};

class Obsidian : public Material{
public:
	glm::vec4 mat_ambient = glm::vec4(0.05375f, 0.05f, 0.06625f, 0.82f);
	glm::vec4 mat_diffuse = glm::vec4(0.18275f, 0.17f, 0.22525f, 0.82f);
	glm::vec4 mat_specular = glm::vec4(0.332741f, 0.328634f, 0.346435f, 0.82f);
	float shine = 38.4f;
};

class Bronze : public Material{
public:
	glm::vec4 mat_ambient = glm::vec4(0.2125f, 0.1275f, 0.054f, 1.0f);
	glm::vec4 mat_diffuse = glm::vec4(0.714f, 0.4284f, 0.18144f, 1.0f);
	glm::vec4 mat_specular = glm::vec4(0.393548f, 0.271906f, 0.166721f, 1.0f);
	float shine = 25.6f;
};

class Chrome : public Material{
public:
	glm::vec4 mat_ambient = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
	glm::vec4 mat_diffuse = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	glm::vec4 mat_specular = glm::vec4(0.774597f, 0.774597f, 0.774597f, 1.0f);
	float shine = 76.8f;
};

class Gold : public Material{
public:
	glm::vec4 mat_ambient = glm::vec4(0.24725f, 0.1995f, 0.0745f, 1.0f);
	glm::vec4 mat_diffuse = glm::vec4(0.75164f, 0.60648f, 0.22648f, 1.0f);
	glm::vec4 mat_specular = glm::vec4(0.628281f, 0.555802f, 0.366065f, 1.0f);
	float shine = 51.2f;
};

class Silver : public Material{
public:
	glm::vec4 mat_ambient = glm::vec4(0.19225f, 0.19225f, 0.19225f, 1.0f);
	glm::vec4 mat_diffuse = glm::vec4(0.50754f, 0.50754f, 0.50754f, 1.0f);
	glm::vec4 mat_specular = glm::vec4(0.508273f, 0.508273f, 0.508273f, 1.0f);
	float shine = 51.2f;
};

class BlackRubber : public Material{
public:
	glm::vec4 mat_ambient = glm::vec4(0.02f, 0.02f, 0.02f, 1.0f);
	glm::vec4 mat_diffuse = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
	glm::vec4 mat_specular = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	float shine = 10.0f;
};

#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


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
	
	glm::vec4 mat_ambient;
	glm::vec4 mat_diffuse;
	glm::vec4 mat_specular;
	float shine = 5.0;
	Light m_light;

	Material();
	void useMaterial(Shader& shader);
};

class Obsidian : public Material{
public:
	Obsidian();
};

class Bronze : public Material{
public:
	Bronze();
};

class Chrome : public Material{
public:
	Chrome();
};

class Gold : public Material{
public:
	Gold();
};

class Silver : public Material{
public:
	Silver();
};

class BlackRubber : public Material{
public:
	BlackRubber();
};

#endif


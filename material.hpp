//#pragma once
#ifndef __MATERIAL_H__
#define __MATERIAL_H__


class Material {
public:
	
};

class Obsidian : public Material{
public:
	glm::vec4 mat_ambient(0.05375f, 0.05f, 0.06625f, 0.82f);
	glm::vec4 mat_diffuse(0.18275f, 0.17f, 0.22525f, 0.82f);
    glm::vec4 mat_specular(0.332741f, 0.328634f, 0.346435f, 0.82f);
	float shine = 38.4f;
};
class Bronze : public Material{
public:
	glm::vec4 mat_ambient(0.2125f, 0.1275f, 0.054f, 1.0f);
	glm::vec4 mat_diffuse(0.714f, 0.4284f, 0.18144f, 1.0f);
    glm::vec4 mat_specular(0.393548f, 0.271906f, 0.166721f, 1.0f);
	float shine = 25.6f;
};
class Chrome : public Material{
public:
	glm::vec4 mat_ambient(0.25f, 0.25f, 0.25f, 1.0f);
	glm::vec4 mat_diffuse(0.4f, 0.4f, 0.4f, 1.0f);
    glm::vec4 mat_specular(0.774597f, 0.774597f, 0.774597f, 1.0f);
	float shine = 76.8f;
};
class Gold : public Material{
public:
	glm::vec4 mat_ambient(0.24725f, 0.1995f, 0.0745f, 1.0f);
	glm::vec4 mat_diffuse(0.75164f, 0.60648f, 0.22648f, 1.0f);
    glm::vec4 mat_specular(0.628281f, 0.555802f, 0.366065f, 1.0f);
	float shine = 51.2f;
};
class Silver : public Material{
public:
	glm::vec4 mat_ambient(0.19225f, 0.19225f, 0.19225f, 1.0f);
	glm::vec4 mat_diffuse(0.50754f, 0.50754f, 0.50754f, 1.0f);
    glm::vec4 mat_specular(0.508273f, 0.508273f, 0.508273f, 1.0f);
	float shine = 51.2f;
};
class BlackRubber : public Material{
public:
	glm::vec4 mat_ambient(0.02f, 0.02f, 0.02f, 1.0f);
	glm::vec4 mat_diffuse(0.01f, 0.01f, 0.01f, 1.0f);
    glm::vec4 mat_specular(0.4f, 0.4f, 0.4f, 1.0f);
	float shine = 10.0f;
};

#endif


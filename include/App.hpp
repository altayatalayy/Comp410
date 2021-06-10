#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <chrono>

#include "util.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Window.hpp"

#ifndef __APP_H__
#define __APP_H__

std::chrono::milliseconds get_time();

class App{
public:

	Shader shader;
	//ComputeShader compute_shader;
	Camera *m_camera;
	Window m_window;
	float m_fov = 45.0f;

	glm::mat4 m_PV;

	std::vector<Model> m_models;
	Model* sphere;
	Model* cube;
	std::vector<Material> m_materials;

	unsigned long int frame_count = 0;
	std::chrono::milliseconds start_time;

	particleSystem ps;
	unsigned int m_numParticles = 20;

	Material material;
	Chrome chrome;
	Gold gold;
	Silver silver;
	Bronze bronze;
	Obsidian obsidian;
	BlackRubber black_rubber;

	static App* getInstance();
	App();
	~App();
	void setMaterial(int number);
	glm::mat4 getProjectionMatrix();
	glm::mat4& getPVMatrix();
	void run();
	void draw();
	float getFps();
};

#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <chrono>

#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Window.hpp"
#include "util.hpp"


#ifndef __APP_H__
#define __APP_H__

static std::chrono::milliseconds get_time(){
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds >(
			    std::chrono::system_clock::now().time_since_epoch()
			);
	return ms;
}


class App{
public:

	static App* getInstance(){
		static App instance;
		return &instance;
	}

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


	App(){
		tetrahedron(NumTimesToSubdivide);
		colorcube();
		m_camera = Camera::getInstance();
		glewExperimental = GL_TRUE;
		glewInit();
		GLCall(glEnable( GL_DEPTH_TEST ));
		GLCall(glEnable(GL_CULL_FACE));
		init_rope(m_numParticles, ps);

		shader = Shader("shaders/vshader.glsl",  "shaders/fshader.glsl");
		//compute_shader = ComputeShader("shaders/compute.glsl");
		shader.Bind();
		GLint vPosition = shader.getAttribLocation("vPosition");
		GLint vNormal = shader.getAttribLocation("vNormal");
		sphere = new Model(NumVerticesSphere, pointSphere, normals, vPosition, vNormal);
		cube = new Model(36, points, normalsCube, vPosition, vNormal);
		cube->setScale(0.3f, 0.15f, 0.1f);
		black_rubber.useMaterial(shader);

	}

	~App(){
		ps.stop();
	}

	void setMaterial(int number){
		if(number == 1){
			black_rubber.useMaterial(shader);
		}
		if(number == 2){
			gold.useMaterial(shader);
		}
		if(number == 3){
			bronze.useMaterial(shader);
		}
		if(number == 4){
			chrome.useMaterial(shader);
		}
		if(number == 5){
			obsidian.useMaterial(shader);
		}
		if(number == 6){
			silver.useMaterial(shader);
		}

	}

	glm::mat4 getProjectionMatrix(){
		return glm::ortho(-2.0f, 2.0f, -3.0f, 3.0f, -1.0f, 1.0f) * glm::perspective(m_fov, m_window.getAR(), 0.1f, 100.0f);
	}

	glm::mat4& getPVMatrix(){
		if(m_camera->hasChanged()){
			glm::mat4 PV = glm::mat4(1.0f);
			glm::mat4 view = m_camera->getView();
			glm::mat4 projection = getProjectionMatrix();
			PV = projection * view;
			m_PV = PV;
		}
		return m_PV;
	}

	void run(){
		GLCall(glClearColor(0.7f, 0.7f, 0.7f, 1.0f));
		start_time = get_time();
		/* Loop until the user closes the window */
		int n = 0;
		while(!m_window.shouldClose()) {
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			draw();
			m_window.swapBuffers();
			n++;
			if(n % 20 == 0){
				printf("fps = %f\n", getFps());
				ps.run();
				//ps.applyWind(m_numParticles-3);
			}
		}
	}

	void draw(){
		//ps.update(0.01f);
		cube->Bind();
		glm::mat4 pv = getPVMatrix();
		glm::mat4 mm = cube->getModelMatrix(0.0f, 1.4f, 0.0f);
		glm::mat4 mvp = pv * mm;
		shader.Bind();
		shader.setUniformMat4("u_MVP", mvp);
		shader.setUniformMat4("u_Model", mm);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, cube->numVertices));

		for(int i = 0; i<m_numParticles; i++){
			//printf("%f\n", ps.get_sim_time());
			auto pos = ps.get_positions();
			sphere->Bind();
			glm::mat4 mm = sphere->getModelMatrix(pos[i*3], pos[i*3+1], pos[i*3+2]);
			glm::mat4 mvp = pv * mm;
			shader.Bind();
			shader.setUniformMat4("u_MVP", mvp);
			shader.setUniformMat4("u_Model", mm);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, sphere->numVertices));
		}
		frame_count++;
	}

	float getFps(){
		float fps;
		fps = (float)frame_count / (float)(get_time() - start_time).count();
		return fps * 1000.0f;
	}
};

#endif

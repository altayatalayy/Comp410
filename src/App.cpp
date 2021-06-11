#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "App.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Window.hpp"
#include "util.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

std::chrono::milliseconds get_time(){
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds >(
			    std::chrono::system_clock::now().time_since_epoch()
			);
	return ms;
}



App* App::getInstance(){
	static App instance;
	return &instance;
}


App::App(){
	Data sphere_data = tetrahedron();
	Data cube_data = colorcube();
	m_camera = Camera::getInstance();
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_CULL_FACE));
	init_rope(m_numParticles, ps);

	shader = Shader("shaders/vshader.glsl",  "shaders/fshader.glsl");
	//compute_shader = ComputeShader("shaders/compute.glsl");
	shader.Bind();
	GLint vPosition = shader.getAttribLocation("vPosition");
	GLint vNormal = shader.getAttribLocation("vNormal");
	sphere = new Model(sphere_data, vPosition, vNormal);
	cube = new Model(cube_data, vPosition, vNormal);
	cube->setScale(0.3f, 0.15f, 0.1f);
	black_rubber.useMaterial(shader);

}

App::~App(){
	ps.stop();
}

void App::setMaterial(int number){
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

glm::mat4 App::getProjectionMatrix(){
	return glm::ortho(-2.0f, 2.0f, -3.0f, 3.0f, -1.0f, 1.0f) * glm::perspective(m_fov, m_window.getAR(), 0.1f, 100.0f);
}

glm::mat4& App::getPVMatrix(){
	if(m_camera->hasChanged()){
		glm::mat4 PV = glm::mat4(1.0f);
		glm::mat4 view = m_camera->getView();
		glm::mat4 projection = getProjectionMatrix();
		PV = projection * view;
		m_PV = PV;
	}
	return m_PV;
}

void App::run(){
	GLCall(glClearColor(0.7f, 0.7f, 0.7f, 1.0f));
	start_time = get_time();
	/* Loop until the user closes the window */
	int n = 0;
	while(!m_window.shouldClose()) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Particle System Menu");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Select Material");
			if(ImGui::Button("Black Rubber")){
				setMaterial(1);
			}
			if(ImGui::Button("Gold")){
				setMaterial(2);
			}
			if(ImGui::Button("Bronze")){
				setMaterial(3);
			}
			if(ImGui::Button("Chrome")){
				setMaterial(4);
			}
			if(ImGui::Button("Obsidian")){
				setMaterial(5);
			}
			if(ImGui::Button("Silver")){
				setMaterial(6);
			}

			ImGui::End();
		}
		ImGui::Render();
		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		draw();
		m_window.swapBuffers();
		n++;
		if(n % 20 == 0){
			//printf("fps = %f\n", getFps());
			ps.run();
			//ps.applyWind(m_numParticles-3);
		}
	}
}

void App::draw(){
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

float App::getFps(){
	float fps;
	fps = (float)frame_count / (float)(get_time() - start_time).count();
	return fps * 1000.0f;
}


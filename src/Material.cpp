#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Material.hpp"
#include "Shader.hpp"

Material::Material(){
	mat_ambient = glm::vec4( 1.0, 0.0, 1.0, 1.0 );
	mat_diffuse = glm::vec4( 1.0, 0.8, 0.0, 1.0 );
	mat_specular = glm::vec4( 1.0, 0.0, 1.0, 1.0 );
	shine = 5.0;
}


void Material::useMaterial(Shader& shader){
	glm::vec4 ambient_product = m_light.light_ambient * mat_ambient;
	glm::vec4 diffuse_product = m_light.light_diffuse * mat_diffuse;
	glm::vec4 specular_product = m_light.light_specular * mat_specular;

	shader.setUniform4f("LightPosition", m_light.light_position);
	shader.setUniform4f("AmbientProduct", ambient_product);
	shader.setUniform4f("DiffuseProduct", diffuse_product);
	shader.setUniform4f("SpecularProduct", specular_product);
	shader.setUniform1f("Shininess", shine);
}



Obsidian::Obsidian(){
	mat_ambient = glm::vec4(0.05375f, 0.05f, 0.06625f, 0.82f);
	mat_diffuse = glm::vec4(0.18275f, 0.17f, 0.22525f, 0.82f);
	mat_specular = glm::vec4(0.332741f, 0.328634f, 0.346435f, 0.82f);
	shine = 38.4f;
}

Bronze::Bronze(){
	mat_ambient = glm::vec4(0.2125f, 0.1275f, 0.054f, 1.0f);
	mat_diffuse = glm::vec4(0.714f, 0.4284f, 0.18144f, 1.0f);
	mat_specular = glm::vec4(0.393548f, 0.271906f, 0.166721f, 1.0f);
	shine = 25.6f;
}

Chrome::Chrome(){
	mat_ambient = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
	mat_diffuse = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	mat_specular = glm::vec4(0.774597f, 0.774597f, 0.774597f, 1.0f);
	shine = 76.8f;
}

Gold::Gold(){
	mat_ambient = glm::vec4(0.24725f, 0.1995f, 0.0745f, 1.0f);
	mat_diffuse = glm::vec4(0.75164f, 0.60648f, 0.22648f, 1.0f);
	mat_specular = glm::vec4(0.628281f, 0.555802f, 0.366065f, 1.0f);
	shine = 51.2f;
}

Silver::Silver(){
	mat_ambient = glm::vec4(0.19225f, 0.19225f, 0.19225f, 1.0f);
	mat_diffuse = glm::vec4(0.50754f, 0.50754f, 0.50754f, 1.0f);
	mat_specular = glm::vec4(0.508273f, 0.508273f, 0.508273f, 1.0f);
	shine = 51.2f;
}

BlackRubber::BlackRubber(){
	mat_ambient = glm::vec4(0.02f, 0.02f, 0.02f, 1.0f);
	mat_diffuse = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
	mat_specular = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	shine = 10.0f;
}




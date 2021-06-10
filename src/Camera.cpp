#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera(){
	m_position = glm::vec3(0.0f, 0.0f, 1.0f);
	m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera* Camera::getInstance(){
	static Camera instance;
	return &instance;
}

glm::mat4 Camera::getView() const{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::moveForward(void){
	m_position += m_speed * m_front;
	m_changed = true;
}

void Camera::moveBackward(void){
	m_position -= m_speed * m_front;
	m_changed = true;
}

void Camera::moveRight(void){
	m_position += glm::normalize(glm::cross(m_front, m_up)) * m_speed;
	m_changed = true;
}

void Camera::moveLeft(void){
	m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_speed;
	m_changed = true;
}

bool Camera::hasChanged(){
	if(m_changed){
		m_changed = false;
		return true;
	}
	return false;
}




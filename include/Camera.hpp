#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera{
public:
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_front;
	int n = 0;
	bool m_changed = true;
	float m_speed = 0.05f;

	Camera();
	static Camera* getInstance();
	glm::mat4 getView() const;
	void moveForward(void);
	void moveBackward(void);
	void moveRight(void);
	void moveLeft(void);
	bool hasChanged();

};

#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
#include "util.hpp"

#ifndef __WINDOW_H__
#define __WINDOW_H__

class Window{
public:
	int m_width = 640, m_height = 480;
	GLFWwindow* m_window;

	Window();
	~Window();	
	bool shouldClose();
	void swapBuffers();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	float getAR();

	

};

#endif

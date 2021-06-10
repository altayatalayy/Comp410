#include "Camera.hpp"
#include "App.hpp"

#ifndef __WINDOW_H__
#define __WINDOW_H__
class Window{
public:
	int m_width = 640, m_height = 480;
	GLFWwindow* m_window;

	Window(){

		/* Initialize the library */
		if (!glfwInit())
			return;

		/* Create a windowed mode window and its OpenGL context */
		m_window = glfwCreateWindow(m_width, m_height, "Comp 410 Project", NULL, NULL);
		if (!m_window) {
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_window);
		glfwSetKeyCallback(m_window, key_callback);
	}

	~Window(){
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}	

	bool shouldClose(){
		return glfwWindowShouldClose(m_window);
	}

	void swapBuffers(){
		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
		if (key == GLFW_KEY_W && action == GLFW_PRESS){
			printf("Move camera forward\n");
			Camera *camera = Camera::getInstance();
			camera->moveForward();
		}
		else if(key == GLFW_KEY_A && action == GLFW_PRESS){
			printf("Move camera LEFT\n");
			Camera *camera = Camera::getInstance();
			camera->moveLeft();
		}
		else if(key == GLFW_KEY_S && action == GLFW_PRESS){
			printf("Move camera backward\n");
			Camera *camera = Camera::getInstance();
			camera->moveBackward();
		}
		else if(key == GLFW_KEY_D && action == GLFW_PRESS){
			printf("Move camera right\n");
			Camera *camera = Camera::getInstance();
			camera->moveRight();
		}
		
		/*
		else if(key == GLFW_KEY_1 && action == GLFW_PRESS){
			printf("1\n");
			App *app = App::getInstance();
			app->setMaterial(1);
		}
		else if(key == GLFW_KEY_2 && action == GLFW_PRESS){
			printf("2\n");
			App *app = App::getInstance();
			app->setMaterial(2);
		}
		else if(key == GLFW_KEY_3 && action == GLFW_PRESS){
			printf("3\n");
			App *app = App::getInstance();
			app->setMaterial(3);
		}
		else if(key == GLFW_KEY_4 && action == GLFW_PRESS){
			printf("4\n");
			App *app = App::getInstance();
			app->setMaterial(4);
		}
		else if(key == GLFW_KEY_5 && action == GLFW_PRESS){
			printf("5\n");
			App *app = App::getInstance();
			app->setMaterial(5);
		}
		else if(key == GLFW_KEY_6 && action == GLFW_PRESS){
			printf("6\n");
			App *app = App::getInstance();
			app->setMaterial(6);
			
		}
		*/
		
	}

	float getAR(){
		return (float)m_width / (float)m_height;
	}

	

};

#endif
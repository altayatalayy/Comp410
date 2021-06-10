#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera{
public:
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_front;

	//static Camera *instance;
	
	int n = 0;

	bool m_changed = true;


	float m_speed = 0.05f;

	Camera(){
		m_position = glm::vec3(0.0f, 0.0f, 1.0f);
		m_front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	static Camera* getInstance(){
		static Camera instance;
		return &instance;
	}

	glm::mat4 getView() const{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void moveForward(void){
		m_position += m_speed * m_front;
		m_changed = true;
	}

	void moveBackward(void){
		m_position -= m_speed * m_front;
		m_changed = true;
	}

	void moveRight(void){
		m_position += glm::normalize(glm::cross(m_front, m_up)) * m_speed;
		m_changed = true;
	}

	void moveLeft(void){
		m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_speed;
		m_changed = true;
	}

	bool hasChanged(){
		if(m_changed){
			m_changed = false;
			return true;
		}
		return false;
	}

};

#endif

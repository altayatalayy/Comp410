#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include "InitShader.hpp"

void GLLogCall(const char* func_name, const int line_num){
	while(GLenum err = glGetError()){
		std::cout << "[OpenGL Error] (" << err << ") function: "  << func_name << " line : " << line_num << std::endl;
	}
}

#define GLCall(x) while(glGetError() != GL_NO_ERROR);\
					x;\
					GLLogCall(__PRETTY_FUNCTION__, __LINE__)
#define point4 glm::vec4
const int NumTimesToSubdivide = 5;
const int NumTriangles = 4096;
const int NumVerticesSphere = 3 * NumTriangles;

point4 pointSphere[NumVerticesSphere];
glm::vec3 normals[NumVerticesSphere];

const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

glm::vec3 cross(glm::vec4 a, glm::vec4 b){
	glm::vec3 a1 = glm::vec3(a.x, a.y, a.z);
	glm::vec3 b1 = glm::vec3(b.x, b.y, b.z);
	return glm::cross(a1, b1);
}

int IndexSphere = 0;
void triangle( const point4& a, const point4& b, const point4& c ){
	glm::vec3 normal = glm::normalize(cross(b - a, c - b));
	normals[IndexSphere] = normal; pointSphere[IndexSphere] = a; IndexSphere++;
	normals[IndexSphere] = normal; pointSphere[IndexSphere] = b; IndexSphere++;
	normals[IndexSphere] = normal; pointSphere[IndexSphere] = c; IndexSphere++;
}

const point4 unit( const point4& p ){
	float len = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
	glm::vec4 t;
	if ( len > DivideByZeroTolerance) {
		t = p / len;
		t.w = 1.0;
	}
	return t;
}

void divide_triangle( const point4& a, const point4& b, const point4& c, int count ){
	if ( count > 0 ) {
		point4 v1 = unit( a + b );
		point4 v2 = unit( a + c );
		point4 v3 = unit( b + c );
		divide_triangle( a, v1, v2, count - 1 );
		divide_triangle( c, v2, v3, count - 1 );
		divide_triangle( b, v3, v1, count - 1 );
		divide_triangle( v1, v3, v2, count - 1 );
	} else {
		triangle( a, b, c );
	}
}

void tetrahedron( int count ){
	point4 v[4] = {
		glm::vec4( 0.0, 0.0, 1.0, 1.0 ),
		glm::vec4( 0.0, 0.942809, -0.333333, 1.0 ),
		glm::vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
		glm::vec4( 0.816497, -0.471405, -0.333333, 1.0 )
	};
	divide_triangle( v[0], v[1], v[2], count );
	divide_triangle( v[3], v[2], v[1], count );
	divide_triangle( v[0], v[3], v[1], count );
	divide_triangle( v[0], v[2], v[3], count );
}

#define BUFFER_OFFSET(x) ((GLvoid*)x)
class Model{
public:
	GLuint vao;
	unsigned int numVertices = NumVerticesSphere;
	Model(GLuint vPosition, GLuint vNormal){
		tetrahedron(NumTimesToSubdivide);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pointSphere) + sizeof(normals), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointSphere), pointSphere);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(pointSphere), sizeof(normals), normals);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vNormal);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(pointSphere)));
	}

	glm::mat4 getModelMatrix(float x, float y, float z){
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, glm::vec3(x, y, z));
		mat = glm::scale(mat, glm::vec3(0.01f));
		return mat;
	}
};

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
	}

	float getAR(){
		return (float)m_width / (float)m_height;
	}

	

};


#include <unordered_map>

class Shader{
public:
	GLuint m_program;
	std::unordered_map<std::string, GLint> m_uniforms;

	Shader(){
	}

	Shader(const std::string& vshader, const std::string& fshader){
		m_program = InitShader(vshader.c_str(), fshader.c_str());
	}

	~Shader(){
		GLCall(glDeleteShader(m_program));
	}

	GLint getUniformLocation(const std::string& name){
		GLint location;
		if(m_uniforms.find(name) == m_uniforms.end()){
			GLCall(location = glGetUniformLocation(m_program, name.c_str()));
			if(location == -1){
				std::cout << "Uniform: " << name << " Location not found" << std::endl;
			}
			m_uniforms[name] = location;
		}else{
			location = m_uniforms.at(name);
		}
		return location;
	}

	GLint getAttribLocation(const std::string& name){
		GLint location;
		GLCall(location = glGetAttribLocation(m_program, name.c_str()));
		return location;
	}

	void setUniformMat4(const std::string& name, glm::mat4& mat){
		GLint location = getUniformLocation(name);
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat)));
	}

	void Bind(){
		GLCall(glUseProgram(m_program));
	}
};

class ComputeShader : public Shader{
public:

	ComputeShader(){

	}

	ComputeShader(const std::string& file){
		compile(file);	
	}

	void compile(const std::string& file){
		char * source = readShaderSource(file.c_str());
		GLuint shader = glCreateShader(GL_COMPUTE_SHADER);			
		glShaderSource(shader, 1, (const GLchar**)&source, NULL);
		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if(!compiled){
			printf("Compute Not compiled\n");
			GLint  logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete [] logMsg;
			exit( EXIT_FAILURE );
		}

		m_program = glCreateProgram();
		glAttachShader(m_program, shader);
		glLinkProgram(m_program);

		GLint linked;
		glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
		if(!linked){
			printf("Compute not linked\n");
			GLint  logSize;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog(m_program, logSize, NULL, logMsg );
			std::cerr << logMsg << std::endl;
			delete [] logMsg;
			exit( EXIT_FAILURE );
		}

	}
};

#include "psys.hpp"

void init_rope(int n, particleSystem& ps){
	std::vector<particle> particles;
	float dy = 0.05f;
	for(int i=0; i<n; i++){
		particle p = particle(position_t(0.0f, 0.5f - (float)i*dy, 0.0f), 0.035f, 0.001f);
		if(i == 0){
			p.fix();
		}
		particles.push_back(std::move(p));	
	}
	ps.add_particles(particles);
}

#include <chrono>
static std::chrono::milliseconds get_time(){
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds >(
			    std::chrono::system_clock::now().time_since_epoch()
			);
	return ms;
}

class App{
public:
	Shader shader;
	//ComputeShader compute_shader;
	Camera *m_camera;
	Window m_window;
	float m_fov = 45.0f;

	glm::mat4 m_PV;

	std::vector<Model> m_models;

	unsigned long int frame_count = 0;
	std::chrono::milliseconds start_time;

	particleSystem ps;
	unsigned int m_numParticles = 100;

	App(){
		m_camera = Camera::getInstance();
		GLCall(glEnable( GL_DEPTH_TEST ));
		GLCall(glEnable(GL_CULL_FACE));
		init_rope(m_numParticles, ps);
		glewExperimental = GL_TRUE;
		glewInit();
		shader = Shader("shaders/vshader.glsl",  "shaders/fshader.glsl");
		//compute_shader = ComputeShader("shaders/compute.glsl");
		shader.Bind();
		GLint vPosition = shader.getAttribLocation("vPosition");
		GLint vNormal = shader.getAttribLocation("vNormal");
		Model sphere(vPosition, vNormal);
		m_models.push_back(sphere);
	}

	~App(){
		ps.stop();
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
		ps.run();
		while(!m_window.shouldClose()) {
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			draw();
			m_window.swapBuffers();
			n++;
			if(n % 20 == 0){
				printf("fps = %f\n", getFps());
			}
		}
	}

	void draw(){
		//ps.update(0.01f);
		for(int i = 0; i<m_numParticles; i++){
			//printf("%f\n", ps.get_sim_time());
			auto pos = ps.get_positions();
			Model& model = m_models[0];
			GLCall(glBindVertexArray(model.vao));
			glm::mat4 mvp = getPVMatrix() * model.getModelMatrix(pos[i*3], pos[i*3+1], pos[i*3+2]);
			shader.Bind();
			shader.setUniformMat4("u_MVP", mvp);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, model.numVertices));
		}
		frame_count++;
	}

	float getFps(){
		float fps;
		fps = (float)frame_count / (float)(get_time() - start_time).count();
		return fps * 1000.0f;
	}
};

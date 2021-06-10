#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef __UTIL_H__
#define __UTIL_H__

#define point4 glm::vec4
typedef struct Data{
	unsigned int numVertices;
	point4* vertices;
	glm::vec3* normals;
}Data;

void GLLogCall(const char* func_name, const int line_num);

#define GLCall(x) while(glGetError() != GL_NO_ERROR);\
					x;\
					GLLogCall(__PRETTY_FUNCTION__, __LINE__)


#define BUFFER_OFFSET(x) ((GLvoid*)(x))

glm::vec3 cross(glm::vec4 a, glm::vec4 b);
void quad( int a, int b, int c, int d );
Data colorcube();
void triangle( const point4& a, const point4& b, const point4& c );
const point4 unit( const point4& p );
void divide_triangle( const point4& a, const point4& b, const point4& c, int count );
Data tetrahedron(void);

#include "psys.hpp"
void init_rope(int n, particleSystem& ps);

#endif

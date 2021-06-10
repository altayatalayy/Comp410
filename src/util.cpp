#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "util.hpp"
#include "psys.hpp"

point4 points[36];
const int NumTimesToSubdivide = 5;
const int NumTriangles = 4096;
const int NumVerticesSphere = 3 * NumTriangles;
point4 pointSphere[NumVerticesSphere];
glm::vec3 normals[NumVerticesSphere];
const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);
glm::vec3 normalsCube[36];

void GLLogCall(const char* func_name, const int line_num){
	while(GLenum err = glGetError()){
		std::cout << "[OpenGL Error] (" << err << ") function: "  << func_name << " line : " << line_num << std::endl;
	}
}

glm::vec3 cross(glm::vec4 a, glm::vec4 b){
	glm::vec3 a1 = glm::vec3(a.x, a.y, a.z);
	glm::vec3 b1 = glm::vec3(b.x, b.y, b.z);
	return glm::cross(a1, b1);
}


point4 vertices[8] = {
	point4( -0.5, -0.5,  0.5, 1.0 ),
	point4( -0.5,  0.5,  0.5, 1.0 ),
	point4(  0.5,  0.5,  0.5, 1.0 ),
	point4(  0.5, -0.5,  0.5, 1.0 ),
	point4( -0.5, -0.5, -0.5, 1.0 ),
	point4( -0.5,  0.5, -0.5, 1.0 ),
	point4(  0.5,  0.5, -0.5, 1.0 ),
	point4(  0.5, -0.5, -0.5, 1.0 )
};


int Index = 0;
void quad( int a, int b, int c, int d ) {
	// Initialize temporary vectors along the quad’s edge to
	//   compute its face normal
	glm::vec4 u = vertices[b] - vertices[a];
	glm::vec4 v = vertices[c] - vertices[b];
	glm::vec3 normal = glm::normalize( cross(u, v) );
	normalsCube[Index] = normal; points[Index] = vertices[a]; Index++;
	normalsCube[Index] = normal; points[Index] = vertices[b]; Index++;
	normalsCube[Index] = normal; points[Index] = vertices[c]; Index++;
	normalsCube[Index] = normal; points[Index] = vertices[a]; Index++;
	normalsCube[Index] = normal; points[Index] = vertices[c]; Index++;
	normalsCube[Index] = normal; points[Index] = vertices[d]; Index++;
}

Data colorcube(){
	quad( 1, 0, 3, 2 );
	quad( 2, 3, 7, 6 );
	quad( 3, 0, 4, 7 );
	quad( 6, 5, 1, 2 );
	quad( 4, 5, 6, 7 );
	quad( 5, 4, 0, 1 );
	Data data{36, points, normalsCube};
	return data;
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

Data tetrahedron(void){
	int count = NumTimesToSubdivide; 
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
	Data data{NumVerticesSphere, pointSphere, normals};
	return data;
}


void init_rope(int n, particleSystem& ps){
	std::vector<particle> particles;
	float dy = 0.10f;
	for(int i=0; i<n; i++){
		particle p = particle(position_t(0.0f, 1.3f - (float)i*dy, 0.0f), 0.035f, 0.001f);
		if(i == 0){
			p.fix();
		}
		particles.push_back(std::move(p));	
	}
	ps.add_particles(particles);
}



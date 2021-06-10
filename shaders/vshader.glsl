#version 330

in vec4 vPosition;
in vec3 vNormal;

uniform mat4 u_MVP;

void main(){
	gl_Position = u_MVP * vPosition;
}

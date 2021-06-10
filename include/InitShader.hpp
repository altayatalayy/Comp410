#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#ifndef __INITS_H__
#define __INITS_H__

// Create a NULL-terminated string by reading the provided file
static char* readShaderSource(const char* shaderFile); 


// Create a GLSL program object from vertex and fragment shader files
GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
#endif

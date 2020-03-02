#ifndef PROGRAM_OBJECT_H_
#define PROGRAM_OBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

bool readShaderSource(const char* name, std::vector<GLchar>& buffer);

GLuint loadProgramObject(const char* vert, const char* frag);

GLuint createProgramObject(const char* vsrc, const char* fsrc);

GLboolean printShaderInfoLog(GLuint shader, const char* str);

GLboolean printProgramInfoLog(GLuint program);

#endif  // PROGRAM_OBJECT_H_
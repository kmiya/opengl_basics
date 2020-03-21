#ifndef PROGRAM_OBJECT_H_
#define PROGRAM_OBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

bool readShaderSource(const char* const name, std::vector<GLchar>& buffer);

GLuint loadProgramObject(const char* const vert, const char* const frag);

GLuint createProgramObject(const char* const vsrc, const char* const fsrc);

GLboolean printShaderInfoLog(GLuint shader, const char* const str);

GLboolean printProgramInfoLog(GLuint program);

#endif  // PROGRAM_OBJECT_H_
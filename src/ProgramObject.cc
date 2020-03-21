#include "ProgramObject.h"

#include <fstream>
#include <iostream>
#include <vector>

bool readShaderSource(const char* const name, std::vector<GLchar>& buffer) {
  if (!name) {
    return false;
  }

  std::ifstream file(name, std::ios_base::binary);
  if (file.fail()) {
    std::cerr << "Cannot open the source file: " << name << std::endl;
    return false;
  }

  file.seekg(0L, std::ios_base::end);
  const GLsizei length = static_cast<GLsizei>(file.tellg());

  buffer.resize(length + 1);

  file.seekg(0L, std::ios_base::beg);
  file.read(buffer.data(), length);
  buffer[length] = '\0';

  if (file.fail()) {
    std::cerr << "Could not read the file: " << name << std::endl;
    file.close();
    return false;
  }

  file.close();
  return true;
}

GLuint loadProgramObject(const char* const vert, const char* const frag) {
  std::vector<GLchar> vsrc;
  const bool vstat = readShaderSource(vert, vsrc);
  std::vector<GLchar> fsrc;
  const bool fstat = readShaderSource(frag, fsrc);

  return vstat && fstat ? createProgramObject(vsrc.data(), fsrc.data()) : 0;
}

GLuint createProgramObject(const char* const vsrc, const char* const fsrc) {
  const GLuint program = glCreateProgram();

  if (vsrc) {
    const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vobj, 1, &vsrc, nullptr);
    glCompileShader(vobj);

    if (printShaderInfoLog(vobj, "vertex shader"))
      glAttachShader(program, vobj);
    glDeleteShader(vobj);
  }

  if (fsrc) {
    const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fobj, 1, &fsrc, nullptr);
    glCompileShader(fobj);

    if (printShaderInfoLog(fobj, "fragment shader"))
      glAttachShader(program, fobj);
    glDeleteShader(fobj);
  }

  glBindAttribLocation(program, 0, "position");
  glBindFragDataLocation(program, 0, "fragment");
  glLinkProgram(program);

  if (printProgramInfoLog(program))
    return program;

  glDeleteProgram(program);
  return 0;
}

GLboolean printShaderInfoLog(GLuint shader, const char* const str) {
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    std::cerr << "Compile error in " << str << std::endl;
  }

  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

  if (bufSize > 1) {
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog << std::endl;
  }

  return static_cast<GLboolean>(status);
}

GLboolean printProgramInfoLog(GLuint program) {
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (!status) {
    std::cerr << "Link error." << std::endl;
  }

  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

  if (bufSize > 1) {
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }

  return static_cast<GLboolean>(status);
}
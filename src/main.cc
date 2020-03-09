#include "main.h"

#include <iostream>
#include <cstdlib>
#include <memory>

constexpr Object::Vertex rectangleVertex[] = {
  {-0.5, -0.5f},
  {0.5, -0.5f},
  {0.5, 0.5f},
  {-0.5, 0.5f}
};

int main() {
  if (!glfwInit()) {
    std::exit(EXIT_FAILURE);
  }

  atexit(glfwTerminate);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Window window;

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  const GLuint program = loadProgramObject("point.vert", "point.frag");

  // get location of uniform variables
  const GLint aspectLoc = glGetUniformLocation(program, "aspect");

  // create figure data
  std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

  // main loop
  while (window) {
    glClear(GL_COLOR_BUFFER_BIT);

    // enable shader program
    glUseProgram(program);

    // set values to uniform variables
    glUniform1f(aspectLoc, window.getAspect());

    shape->draw();

    window.swapBuffers();
  }

  exit(EXIT_SUCCESS);
}

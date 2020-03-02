#include "main.h"

#include <iostream>
#include <cstdlib>


int main() {
  GLFWwindow* window;
  if (!glfwInit()) {
    std::exit(EXIT_FAILURE);
  }
  // std::cout << "OpenGL:" << std::endl;
  // std::cout << glGetString(GL_VENDOR) << std::endl;
  // std::cout << glGetString(GL_RENDERER) << std::endl;
  // std::cout << glGetString(GL_VERSION) << std::endl;

  atexit(glfwTerminate);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "My Window", nullptr, nullptr);
  if (!window) {
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glfwSwapInterval(1);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  const GLuint program = loadProgramObject("point.vert", "point.frag");

  // main loop
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glfwSwapBuffers(window);
    glfwWaitEvents();
  }

  glfwDestroyWindow(window);

  exit(EXIT_SUCCESS);
}

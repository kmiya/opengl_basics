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

  // get location of uniform variable
  const GLint modelviewLoc = glGetUniformLocation(program, "modelview");
  const GLint projectionLoc = glGetUniformLocation(program, "projection");

  // create figure data
  std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

  // main loop
  while (window) {
    glClear(GL_COLOR_BUFFER_BIT);

    // enable shader program
    glUseProgram(program);

    const GLfloat* const size = window.getSize();
    const GLfloat scale = window.getScale() * 2.0f;
    const GLfloat w = size[0] / scale, h = size[1] / scale;
    const Matrix projection(Matrix::orthogonal(-w, w, -h, h, 1.0f, 10.0f));

    // model transformation matrix
    const GLfloat* const location = window.getLocation();
    const Matrix model(Matrix::translate(location[0], location[1], 0.0f));

    // view transformation matrix
    const Matrix view =
        Matrix::lookat(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // modeview transformation matrix
    const Matrix modelview(view * model);

    glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, modelview.data());
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());

    shape->draw();

    window.swapBuffers();
  }

  exit(EXIT_SUCCESS);
}

#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
 public:
  Window(const int width = 640, const int height = 480,
         const char* title = "Main Window")
      : window(glfwCreateWindow(width, height, title, nullptr, nullptr)){
    if (!window) {
      std::cerr << "Cannot create GLFW window." << std::endl;
      std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, &resize);

    resize(window, width, height);
  }

  virtual ~Window() { glfwDestroyWindow(window); }

  explicit operator bool() {
    glfwWaitEvents();

    // return true if not need to close the window
    return !glfwWindowShouldClose(window);
  }

  inline void swapBuffers() const { glfwSwapBuffers(window); }

  static void resize(GLFWwindow* window, int width, int height) {
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    glViewport(0, 0, fbWidth, fbHeight);

    Window* instance =
        static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (instance) {
      instance->aspect =
          static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
    }
  }

  inline GLfloat getAspect() const { return aspect; }

 private:
  GLFWwindow* window;
  GLfloat aspect;
};

#endif // WINDOW_H
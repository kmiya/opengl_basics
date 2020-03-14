#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
 public:
  Window(const int width = 640, const int height = 480,
         const char* title = "Main Window")
      : window(glfwCreateWindow(width, height, title, nullptr, nullptr)),
        scale(100.0f), location{ 0.0f, 0.0f } {
    if (!window) {
      std::cerr << "Cannot create GLFW window." << std::endl;
      std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    glfwSetScrollCallback(window, wheel);

    glfwSetWindowSizeCallback(window, resize);

    resize(window, width, height);
  }

  virtual ~Window() { glfwDestroyWindow(window); }

  explicit operator bool() {
    glfwWaitEvents();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_RELEASE) {
      double x, y;
      glfwGetCursorPos(window, &x, &y);
      location[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
      location[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];    
    }

    // return true if not need to close the window
    return !glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE);
  }

  inline void swapBuffers() const { glfwSwapBuffers(window); }

  static void resize(GLFWwindow* window, int width, int height) {
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    glViewport(0, 0, fbWidth, fbHeight);

    Window* instance =
        static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (instance) {
      instance->size[0] = static_cast<GLfloat>(width);
      instance->size[1] = static_cast<GLfloat>(height);
    }
  }

  static void wheel(GLFWwindow* window, double x, double y) {
    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (instance) {
      instance->scale += static_cast<GLfloat>(y);
    }
  }

  inline const GLfloat* getSize() const { return size; }

  inline GLfloat getScale() const { return scale; }

  inline const GLfloat* getLocation() const { return location; }

 private:
  GLFWwindow* window;
  GLfloat size[2];
  GLfloat scale;

  // figure position in normalized device coordinates
  GLfloat location[2];
};

#endif // WINDOW_H
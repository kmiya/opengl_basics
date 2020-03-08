#ifndef OBJECT_H_
#define OBJECT_H_

#include <glad/glad.h>


class Object {
 public:
  struct Vertex {
    GLfloat position[2];
  };

  Object(GLint size, GLsizei vertexCount, const Vertex* vertex) {
    // vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertex,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
  }

  virtual ~Object() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
  }

  void bind() const { glBindVertexArray(vao); }

 private:
  GLuint vao;
  GLuint vbo;

  Object(const Object& o) = delete;
  Object& operator=(const Object& o) = delete;
};

#endif  // OBJECT_H_
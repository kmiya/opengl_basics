#ifndef SHAPE_H_
#define SHAPE_H_

#include <memory>

#include "Object.h"

class Shape {
 public:
  Shape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex)
  : object(new Object(size, vertexCount, vertex))
  , vertexCount(vertexCount) {
  }

  void draw() const {
    object->bind();
    execute();
  }

  virtual void execute() const {
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
  }

 protected:
  const GLsizei vertexCount;

 private:

  std::shared_ptr<const Object> object;

};

#endif // SHAPE_H_
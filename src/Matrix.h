#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>
#include <algorithm>
#include <glad/glad.h>

class Matrix {
 public:
  Matrix() {}

  Matrix(const GLfloat *a) { std::copy(a, a + 16, matrix); }

  const GLfloat &operator[](const std::size_t i) const { return matrix[i]; }

  GLfloat &operator[](const std::size_t i) { return matrix[i]; }

  const GLfloat* data() const { return matrix; }

  void loadIdentity() {
    std::fill(matrix, matrix + 16, 0.0f);
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;
  }

  static Matrix identity() const {
    Matrix t;
    t.loadIdentity();
    return t;
  }

  static Matrix translate(const GLfloat x, const GLfloat y, const GLfloat z) const {
    Matrix t;
    t.loadIdentity();
    t[12] = x;
    t[13] = y;
    t[14] = z;

    return t;
  }

  static Matrix scale(const GLfloat x, const GLfloat y, const GLfloat z) const {
    Matrix t;
    t.loadIdentity();
    t[0] = x;
    t[5] = y;
    t[10] = z;

    return t;
  }

  static Matrix rotate(const GLfloat a, const GLfloat x, const GLfloat y, const GLfloat z) const {
    Matrix t;
    const GLfloat d = sqrt(x * x + y * y + z * z);
    if (d > 0.0f) {
      const GLfloat l = x / d, m = y / d, n = z / d;
      const GLfloat l2 = l * l, m2 = m * m, n2 = n * n;
      const GLfloat lm = l * m, mn = m * n, nl = n * l;
      const GLfloat c = cos(a), c1 = 1.0f - c, s = sin(a);
      t.loadIdentity();
      t[0] = (1.0f - l2) * c + l2;
      t[1] = lm * c1 + n * s;
      t[2] = nl * c1 - m * s;
      t[4] = lm * c1 - n * s;
      t[5] = (1.0f - m2) * c + m2;
      t[6] = mn * c1 + l * s;
      t[8] = nl * c1 + m * s;
      t[9] = mn * c1 - l * s;
      t[10] = (1.0f - n2) * c + n2;
    } else {
      t.loadIdentity();
    }
    return t;
  }

  Matrix operator*(const Matrix& m) const {
    Matrix t;
    for (int i = 0; i < 16; ++i) {
      const int j = i & 3, k = i & ~3;
      t[i] =
        matrix[0 + j] * m[k + 0] +
        matrix[4 + j] * m[k + 1] +
        matrix[8 + j] * m[k + 2] +
        matrix[12 + j] * m[k + 3];
    }
  }

private:
  GLfloat matrix[16];

};

#endif // MATRIX_H_
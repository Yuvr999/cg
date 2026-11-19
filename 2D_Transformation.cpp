// Controls: T Translate right | R Rotate | S Scale | 0 Reset | Esc Exit
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

struct Point {
    float x, y;
    Point operator+(Point p) const { return {x + p.x, y + p.y}; }
    Point operator*(float s) const { return {x * s, y * s}; }
    Point operator^(float degrees) const {
        float a = degrees * 3.14159265f / 180.0f;
        return {x * std::cos(a) - y * std::sin(a),
                x * std::sin(a) + y * std::cos(a)};
    }
};

float angle = 0, scale = 1, tx = 0, ty = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Point p[3] = {{100, 100}, {250, 100}, {175, 250}};
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; ++i) {
        Point q = (p[i] * scale) ^ angle;
        q = q + Point{tx, ty};
        glVertex2f(q.x, q.y);
    }
    glEnd();
    glFlush();
}

void key(unsigned char k, int, int) {
    if (k == 't' || k == 'T') tx += 20;
    if (k == 'r' || k == 'R') angle += 10;
    if (k == 's' || k == 'S') scale += 0.1f;
    if (k == '0') { angle = tx = ty = 0; scale = 1; }
    if (k == 27) std::exit(0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformation");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
}

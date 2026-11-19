// Bezier-style recursive branching curve from the practical PDF
#include <GL/glut.h>
#include <cmath>

void branch(float x, float y, float len, float angle, int depth) {
    if (depth == 0) return;
    const float pi = 3.14159265f;
    float r = angle * pi / 180.0f;
    float x2 = x + len * std::cos(r);
    float y2 = y + len * std::sin(r);

    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1.001f; t += 0.05f) {
        float u = 1 - t;
        float xA = x + len * 0.3f * std::cos(r - 20 * pi / 180);
        float xB = x + len * 0.7f * std::cos(r + 20 * pi / 180);
        float yA = y + len * 0.3f * std::sin(r - 20 * pi / 180);
        float yB = y + len * 0.7f * std::sin(r + 20 * pi / 180);
        float X = u*u*u*x + 3*u*u*t*xA + 3*u*t*t*xB + t*t*t*x2;
        float Y = u*u*u*y + 3*u*u*t*yA + 3*u*t*t*yB + t*t*t*y2;
        glVertex2f(X, Y);
    }
    glEnd();
    branch(x2, y2, len * 0.65f, angle - 35, depth - 1);
    branch(x2, y2, len * 0.65f, angle + 35, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    branch(250, 50, 120, 90, 5);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bezier Fractal");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

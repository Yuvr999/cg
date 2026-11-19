#include <GL/glut.h>
#include <cmath>

void koch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }
    float dx = (x2 - x1) / 3.0f, dy = (y2 - y1) / 3.0f;
    float x3 = x1 + dx, y3 = y1 + dy;
    float x4 = x1 + 2 * dx, y4 = y1 + 2 * dy;
    float x5 = (x1 + x2) / 2 - std::sqrt(3.0f) * (y2 - y1) / 6;
    float y5 = (y1 + y2) / 2 + std::sqrt(3.0f) * (x2 - x1) / 6;
    koch(x1, y1, x3, y3, depth - 1);
    koch(x3, y3, x5, y5, depth - 1);
    koch(x5, y5, x4, y4, depth - 1);
    koch(x4, y4, x2, y2, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    koch(100, 150, 400, 150, 4);
    koch(400, 150, 250, 410, 4);
    koch(250, 410, 100, 150, 4);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Koch Snowflake");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

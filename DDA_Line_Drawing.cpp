// Controls: Left-click twice to draw | 1 Simple | 2 Dotted | 3 Dashed | R Reset | Esc Exit
#include <GL/glut.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>

int x1 = 0, y1 = 0, x2 = 0, y2 = 0, clicks = 0, style = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (clicks == 2) {
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        int dx = x2 - x1, dy = y2 - y1;
        int steps = std::max(std::abs(dx), std::abs(dy));
        float x = static_cast<float>(x1), y = static_cast<float>(y1);
        if (steps == 0) glVertex2i(x1, y1);
        for (int i = 0; i <= steps; ++i) {
            if (style == 1 || (style == 2 && i % 5 == 0) ||
                (style == 3 && i % 12 < 7))
                glVertex2i(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));
            if (steps) { x += dx / static_cast<float>(steps); y += dy / static_cast<float>(steps); }
        }
        glEnd();
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clicks == 0) { x1 = x; y1 = 500 - y; clicks = 1; }
        else { x2 = x; y2 = 500 - y; clicks = 2; }
        glutPostRedisplay();
    }
}
void keyboard(unsigned char k, int, int) {
    if (k >= '1' && k <= '3') style = k - '0';
    if (k == 'r' || k == 'R') clicks = 0;
    if (k == 27) std::exit(0);
    glutPostRedisplay();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); glutCreateWindow("DDA Line Drawing");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display); glutMouseFunc(mouse); glutKeyboardFunc(keyboard);
    glutMainLoop(); return 0;
}

// Controls: Left-click twice to draw | 1 Simple | 2 Dotted | 3 Dashed | R Reset | Esc Exit
#include <GL/glut.h>
#include <cstdlib>
#include <algorithm>

int x1 = 0, y1 = 0, x2 = 0, y2 = 0, clicks = 0, style = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-250, 0); glVertex2i(250, 0);
    glVertex2i(0, -250); glVertex2i(0, 250);
    glEnd();

    if (clicks == 2) {
        int x = x1, y = y1;
        int dx = std::abs(x2 - x1), dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy, i = 0;
        glBegin(GL_POINTS);
        while (true) {
            if (style == 1 || (style == 2 && i % 5 == 0) ||
                (style == 3 && i % 12 < 7)) glVertex2i(x, y);
            if (x == x2 && y == y2) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x += sx; }
            if (e2 < dx) { err += dx; y += sy; }
            ++i;
        }
        glEnd();
    }
    glFlush();
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clicks == 0) { x1 = x - 250; y1 = 250 - y; clicks = 1; }
        else { x2 = x - 250; y2 = 250 - y; clicks = 2; }
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
    glutInitWindowSize(500, 500); glutCreateWindow("Bresenham Line Drawing");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display); glutMouseFunc(mouse); glutKeyboardFunc(keyboard);
    glutMainLoop(); return 0;
}

#include <GL/glut.h>

void plot8(int x, int y) {
    glVertex2i(x, y); glVertex2i(-x, y);
    glVertex2i(x, -y); glVertex2i(-x, -y);
    glVertex2i(y, x); glVertex2i(-y, x);
    glVertex2i(y, -x); glVertex2i(-y, -x);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int x = 0, y = 100, decision = 1 - 100;
    glBegin(GL_POINTS);
    while (x <= y) {
        plot8(x, y);
        if (decision < 0) decision += 2*x + 3;
        else { decision += 2*(x-y) + 5; --y; }
        ++x;
    }
    glEnd();
    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); glutCreateWindow("Midpoint Circle Drawing");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display); glutMainLoop(); return 0;
}

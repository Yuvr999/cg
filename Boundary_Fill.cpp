// Left-click inside the rectangle to fill it (4-connected boundary fill)
#include <GL/glut.h>

int seedX = -1, seedY = -1;
bool filled = false;

void boundaryFill(int x, int y) {
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) return; // white boundary
    if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0) return;   // fill colour

    glColor3f(0, 1, 0);
    glBegin(GL_POINTS); glVertex2i(x, y); glEnd();
    glFlush();
    boundaryFill(x + 1, y); boundaryFill(x - 1, y);
    boundaryFill(x, y + 1); boundaryFill(x, y - 1);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 150); glVertex2i(350, 150);
    glVertex2i(350, 350); glVertex2i(150, 350);
    glEnd(); glFlush();
    if (seedX != -1 && !filled) { filled = true; boundaryFill(seedX, seedY); }
}
void mouse(int b, int s, int x, int y) {
    if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN) {
        seedX = x; seedY = 500 - y; filled = false; glutPostRedisplay();
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); glutCreateWindow("Boundary Fill");
    gluOrtho2D(0, 500, 0, 500); glClearColor(0, 0, 0, 1);
    glutDisplayFunc(display); glutMouseFunc(mouse);
    glutMainLoop(); return 0;
}

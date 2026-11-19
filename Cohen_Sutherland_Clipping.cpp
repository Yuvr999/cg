// Controls: Left-click to add polygon vertices | Right-click to finish | C Clip | R Reset
#include <GL/glut.h>
#include <vector>

struct Point { float x, y; };
std::vector<Point> points;
const int xmin = 150, xmax = 350, ymin = 150, ymax = 350;
bool done = false, clipped = false;

int regionCode(Point p) {
    int c = 0;
    if (p.x < xmin) c |= 1;
    if (p.x > xmax) c |= 2;
    if (p.y < ymin) c |= 4;
    if (p.y > ymax) c |= 8;
    return c;
}

void clipLine(Point a, Point b) {
    int c1 = regionCode(a), c2 = regionCode(b);
    while (true) {
        if (!(c1 | c2)) {
            glVertex2f(a.x, a.y); glVertex2f(b.x, b.y); return;
        }
        if (c1 & c2) return;
        int c = c1 ? c1 : c2;
        Point t{};
        if (c & 8) t = {a.x + (b.x-a.x)*(ymax-a.y)/(b.y-a.y), static_cast<float>(ymax)};
        else if (c & 4) t = {a.x + (b.x-a.x)*(ymin-a.y)/(b.y-a.y), static_cast<float>(ymin)};
        else if (c & 2) t = {static_cast<float>(xmax), a.y + (b.y-a.y)*(xmax-a.x)/(b.x-a.x)};
        else t = {static_cast<float>(xmin), a.y + (b.y-a.y)*(xmin-a.x)/(b.x-a.x)};
        if (c == c1) { a = t; c1 = regionCode(a); }
        else { b = t; c2 = regionCode(b); }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin); glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax); glVertex2i(xmin, ymax);
    glEnd();

    if (!points.empty()) {
        glColor3f(0, 0, 1);
        glBegin(done ? GL_LINE_LOOP : GL_LINE_STRIP);
        for (Point p : points) glVertex2f(p.x, p.y);
        glEnd();
    }
    if (clipped && points.size() > 1) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        for (size_t i = 0; i < points.size(); ++i)
            clipLine(points[i], points[(i + 1) % points.size()]);
        glEnd();
    }
    glFlush();
}
void mouse(int b, int s, int x, int y) {
    if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN && !done)
        points.push_back({static_cast<float>(x), static_cast<float>(500-y)});
    if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN) done = true;
    glutPostRedisplay();
}
void keyboard(unsigned char k, int, int) {
    if (k == 'c' || k == 'C') clipped = true;
    if (k == 'r' || k == 'R') { points.clear(); done = clipped = false; }
    glutPostRedisplay();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); glutCreateWindow("Cohen-Sutherland Clipping");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display); glutMouseFunc(mouse); glutKeyboardFunc(keyboard);
    glutMainLoop(); return 0;
}

#include <GL/glut.h>
#include <cmath>

class Shape {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~Shape() = default;
};

class Ball : public Shape {
    float x = 100, y = 100, dx = 3, dy = 2;
public:
    void draw() override {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 360; ++i) {
            float a = i * 3.14159265f / 180.0f;
            glVertex2f(x + 20 * std::cos(a), y + 20 * std::sin(a));
        }
        glEnd();
    }
    void update() override {
        x += dx; y += dy;
        if (x > 480 || x < 20) dx = -dx;
        if (y > 480 || y < 20) dy = -dy;
    }
};

Ball ball;
Shape* shape = &ball;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    shape->draw();
    glutSwapBuffers();
}
void timer(int) {
    shape->update();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500); glutCreateWindow("Bouncing Ball");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display); glutTimerFunc(16, timer, 0);
    glutMainLoop(); return 0;
}

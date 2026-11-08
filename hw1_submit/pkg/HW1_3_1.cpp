#include <cstdlib>
#include <GL/freeglut.h>

float strip[12][2] = {
    {0, 3}, {0, 4}, {1, 3}, {2, 4}, {1, 0}, {2, 1},
    {4, 0}, {3, 1}, {4, 3}, {3, 4}, {5, 3}, {5, 4}
};

float color[10][3] = {
    {0.2, 0.7, 0.8}, {0.9, 0.6, 0.3}, {0.5, 0.7, 0.5}, {0.8, 0.5, 0.8},
    {0.9, 0.8, 0.3}, {0.5, 0.6, 0.9}, {0.9, 0.5, 0.5}, {0.4, 0.8, 0.6},
    {0.7, 0.6, 0.9}, {0.9, 0.6, 0.7}
};

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_FLAT);

    glPolygonMode(GL_BACK, GL_FILL);
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < 12; i++) {
        int k = (i < 2) ? 0 : i - 2;
        glColor3f(color[k][0], color[k][1], color[k][2]);
        glVertex2f(strip[i][0], strip[i][1]);
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < 12; i++)
        glVertex2f(strip[i][0], strip[i][1]);
    glEnd();

    glFlush();
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 6.0, -1.0, 5.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
    if (key == 27) exit(0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutCreateWindow("HW1_3_1");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();
    return 0;
}

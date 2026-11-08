#include <cstdlib>
#include <GL/freeglut.h>

float tri[16][6] = {
    {0, 8, 0, 0, 2, 2},
    {0, 8, 2, 2, 2, 6},
    {0, 8, 2, 6, 5, 8},
    {5, 8, 2, 6, 4, 6},
    {5, 8, 4, 6, 6, 6},
    {5, 8, 6, 6, 8, 6},
    {5, 8, 8, 6, 10, 8},
    {10, 8, 8, 6, 10, 0},
    {10, 0, 8, 6, 8, 2},
    {10, 0, 8, 2, 5, 0},
    {5, 0, 8, 2, 6, 2},
    {5, 0, 6, 2, 4, 2},
    {5, 0, 4, 2, 2, 2},
    {5, 0, 2, 2, 0, 0},
    {4, 6, 4, 2, 6, 2},
    {4, 6, 6, 2, 6, 6}
};

float color[6][3] = {
    {0.9, 0.5, 0.5}, {0.5, 0.8, 0.5}, {0.5, 0.6, 0.9},
    {0.9, 0.8, 0.4}, {0.7, 0.5, 0.8}, {0.4, 0.8, 0.8}
};

void drawTriangles(int fill)
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 16; i++) {
        if (fill) glColor3f(color[i % 6][0], color[i % 6][1], color[i % 6][2]);
        glVertex2f(tri[i][0], tri[i][1]);
        glVertex2f(tri[i][2], tri[i][3]);
        glVertex2f(tri[i][4], tri[i][5]);
    }
    glEnd();
}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    drawTriangles(1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 0.0, 0.0);
    drawTriangles(0);

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
    glOrtho(-1.0, 11.0, -1.0, 9.0, -1.0, 1.0);
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
    glutInitWindowSize(720, 600);
    glutCreateWindow("HW1_1_1");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();
    return 0;
}

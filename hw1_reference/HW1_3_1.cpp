#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct P { float x, y; };

// triangle strip의 정점을 순서대로 적는다.
vector<P> strip = {
    {0, 3}, {0, 4}, {1, 3}, {2, 4}, {1, 0}, {2, 1},
    {4, 0}, {3, 1}, {4, 3}, {3, 4}, {5, 3}, {5, 4}
};

// glOrtho 범위. 그림에 맞게 바꾼다.
float L = -0.5, R = 5.5, B = -0.5, T = 5.5;

const float pal[6][3] = {
    {0.9f, 0.5f, 0.5f}, {0.5f, 0.8f, 0.5f}, {0.5f, 0.6f, 0.9f},
    {0.9f, 0.8f, 0.4f}, {0.7f, 0.5f, 0.8f}, {0.4f, 0.8f, 0.8f}
};

void check()
{
    int n = strip.size();
    cout << "vertices: " << n << ", triangles: " << (n >= 3 ? n - 2 : 0) << "\n";
    for (int i = 0; i + 2 < n; i++) {
        P a = strip[i], b = strip[i + 1], c = strip[i + 2];
        if (i % 2 == 1) swap(a, b);
        float z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        cout << "triangle " << i << ": " << (z > 0 ? "CCW" : (z < 0 ? "CW" : "degenerate")) << "\n";
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_STRIP);
    for (size_t j = 0; j < strip.size(); j++) {
        glColor3fv(pal[j % 6]);
        glVertex2f(strip[j].x, strip[j].y);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);
    for (size_t j = 0; j < strip.size(); j++)
        glVertex2f(strip[j].x, strip[j].y);
    glEnd();
    glFlush();
}

void setup()
{
    glClearColor(1, 1, 1, 1);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(L, R, B, T, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    check();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("HW1 3");
    setup();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop();
    return 0;
}

#include <GL/freeglut.h>
#include <cmath>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

struct P { float x, y; };

// 0~3: 바깥 사각형, 4~7: 왼쪽 구멍, 8~11: 오른쪽 구멍, 12~13: Steiner 정점
vector<P> pts = {
    {0, 0}, {12, 0}, {12, 6}, {0, 6},
    {2, 2}, {5, 2}, {5, 4}, {2, 4},
    {7, 2}, {10, 2}, {10, 4}, {7, 4},
    {6, 0}, {6, 6}
};

vector<array<int, 3>> tris = {
    {0, 4, 7}, {0, 12, 4}, {2, 10, 9}, {4, 12, 5}, {5, 12, 8}, {7, 3, 0},
    {8, 6, 5}, {9, 1, 2}, {9, 12, 1}, {10, 2, 13}, {11, 6, 8}, {12, 9, 8},
    {13, 3, 7}, {13, 6, 11}, {13, 7, 6}, {13, 11, 10}
};

float loopArea(int s)
{
    float a = 0;
    for (int i = 0; i < 4; i++) {
        const P& p = pts[s + i];
        const P& q = pts[s + (i + 1) % 4];
        a += p.x * q.y - q.x * p.y;
    }
    return fabs(a) / 2;
}

float cross2(const P& a, const P& b, const P& c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool inside(const P& p, int s)
{
    float x0 = pts[s].x, y0 = pts[s].y, x1 = pts[s + 2].x, y1 = pts[s + 2].y;
    return p.x > x0 && p.x < x1 && p.y > y0 && p.y < y1;
}

void check()
{
    cout << "vertices: " << pts.size() << ", triangles: " << tris.size() << "\n";
    float sum = 0;
    for (size_t i = 0; i < tris.size(); i++) {
        float c = cross2(pts[tris[i][0]], pts[tris[i][1]], pts[tris[i][2]]);
        sum += fabs(c) / 2;
        cout << "triangle " << i << ": " << (c > 0 ? "CCW" : (c < 0 ? "CW" : "degenerate")) << "\n";
    }
    float expect = loopArea(0) - loopArea(4) - loopArea(8);
    cout << "area sum = " << sum << ", object area = " << expect << "\n";
    for (size_t i = 12; i < pts.size(); i++)
        if (inside(pts[i], 4) || inside(pts[i], 8))
            cout << "vertex " << i << " is inside a hole\n";
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    const float pal[6][3] = {
        {0.9f, 0.5f, 0.5f}, {0.5f, 0.8f, 0.5f}, {0.5f, 0.6f, 0.9f},
        {0.9f, 0.8f, 0.4f}, {0.7f, 0.5f, 0.8f}, {0.4f, 0.8f, 0.8f}
    };
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    for (size_t i = 0; i < tris.size(); i++) {
        glColor3fv(pal[i % 6]);
        glBegin(GL_TRIANGLES);
        for (int k = 0; k < 3; k++)
            glVertex2f(pts[tris[i][k]].x, pts[tris[i][k]].y);
        glEnd();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    for (size_t i = 0; i < tris.size(); i++) {
        glBegin(GL_TRIANGLES);
        for (int k = 0; k < 3; k++)
            glVertex2f(pts[tris[i][k]].x, pts[tris[i][k]].y);
        glEnd();
    }
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
    glOrtho(-1, 13, -0.5, 6.5, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    check();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("HW1 1");
    setup();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop();
    return 0;
}

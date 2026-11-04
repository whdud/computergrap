#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

// E, A는 직접 정해서 바꾼다.
glm::vec3 E(0.0f, 0.0f, 0.0f);
glm::vec3 A(0.0f, 0.0f, 0.0f);
glm::vec3 Up(0.0f, 1.0f, 0.0f);

void printVec(const char* name, const glm::vec3& v)
{
    cout << name << " = (" << v.x << ", " << v.y << ", " << v.z << ")\n";
}

// glm::mat4는 열 우선이라 m[열][행]으로 접근한다.
void printMat(const char* name, const glm::mat4& m)
{
    cout << name << "\n";
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++)
            cout << setw(10) << m[c][r];
        cout << "\n";
    }
}

int main()
{
    if (glm::length(E - A) < 1e-6f || glm::length(glm::cross(Up, E - A)) < 1e-6f) {
        cout << "Set E and A first (E != A, and E - A must not be parallel to Up).\n";
        return 0;
    }

    glm::vec3 los = A - E;
    glm::vec3 zc = glm::normalize(E - A);
    glm::vec3 xc = glm::normalize(glm::cross(Up, zc));
    glm::vec3 yc = glm::cross(zc, xc);

    printVec("E", E);
    printVec("A", A);
    printVec("los", los);
    printVec("x_cam", xc);
    printVec("y_cam", yc);
    printVec("z_cam", zc);

    glm::mat4 R(1.0f);
    for (int j = 0; j < 3; j++) {
        R[j][0] = xc[j];
        R[j][1] = yc[j];
        R[j][2] = zc[j];
    }
    glm::mat4 T = glm::translate(glm::mat4(1.0f), -E);
    glm::mat4 V = R * T;
    glm::mat4 L = glm::lookAt(E, A, Up);

    printMat("R", R);
    printMat("T", T);
    printMat("V = R * T", V);
    printMat("glm::lookAt(E, A, Up)", L);

    float diff = 0.0f;
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            diff = max(diff, fabs(V[c][r] - L[c][r]));
    cout << "max |V - lookAt| = " << diff << "\n";

    glm::vec4 ve = V * glm::vec4(E, 1.0f);
    glm::vec4 va = V * glm::vec4(A, 1.0f);
    cout << "V * E = (" << ve.x << ", " << ve.y << ", " << ve.z << ")\n";
    cout << "V * A = (" << va.x << ", " << va.y << ", " << va.z << ")\n";
    return 0;
}

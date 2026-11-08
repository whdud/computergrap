#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

void printVec(const char *name, glm::vec3 v)
{
    cout << name << " = (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
}

void printMat(const char *name, glm::mat4 m)
{
    cout << name << endl;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++)
            cout << m[col][row] << "\t";
        cout << endl;
    }
}

int main()
{
    glm::vec3 E(3.0f, 2.0f, 4.0f);
    glm::vec3 A(0.0f, 2.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    glm::vec3 zc = glm::normalize(E - A);
    glm::vec3 xc = glm::normalize(glm::cross(up, zc));
    glm::vec3 yc = glm::cross(zc, xc);

    printVec("camera +x", xc);
    printVec("camera +y", yc);
    printVec("camera +z", zc);

    glm::mat4 R(1.0f);
    R[0][0] = xc.x; R[1][0] = xc.y; R[2][0] = xc.z;
    R[0][1] = yc.x; R[1][1] = yc.y; R[2][1] = yc.z;
    R[0][2] = zc.x; R[1][2] = zc.y; R[2][2] = zc.z;

    glm::mat4 T(1.0f);
    T[3][0] = -E.x;
    T[3][1] = -E.y;
    T[3][2] = -E.z;

    glm::mat4 V = R * T;
    glm::mat4 L = glm::lookAt(E, A, up);

    printMat("R", R);
    printMat("T", T);
    printMat("V = R * T", V);
    printMat("glm::lookAt", L);
    return 0;
}

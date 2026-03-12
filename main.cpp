#include <GLFW/glfw3.h>
#include "linmath.h"
#include <iostream>

void interpolacao() {
    //* v1 = (x, y, r, g, b)
    //* std::get<0>(v1) = x
    std::tuple<float, float, float, float, float> v1(-0.5f, -0.5f, 1.f, 0.f, 0.f);
    std::tuple<float, float, float, float, float> v2(0.5f, -0.5f, 0.f, 1.f, 0.f);
    std::tuple<float, float, float, float, float> v3(0.f, 0.5f, 0.f, 0.f, 1.f);
    float x, y;

    glPointSize(5.f);
    glBegin(GL_POINTS);
    //* Q = beta*v1*(1-alpha)+alpha*beta*v2+v3*(1-beta)
    for (float alpha = 0.f; alpha < 1.f; alpha+=0.001f) {
        for (float beta = 0.f; beta < 1.f; beta+=0.001f) {
            x = beta*std::get<0>(v1)*(1-alpha)+alpha*beta*std::get<0>(v2)+std::get<0>(v3)*(1-beta);
            y = beta*std::get<1>(v1)*(1-alpha)+alpha*beta*std::get<1>(v2)+std::get<1>(v3)*(1-beta);
            glColor3f(beta*1.f*(1-alpha), alpha*beta*1.f, 1.f*(1-beta));
            glVertex3f(x, y, 0.f);
        }
    }
    glEnd();
}

// ============================
// Main
// ============================

int main() {
    if(!glfwInit()) {
        //! Error init glfw
        return 1;
    }

    GLFWwindow *window = glfwCreateWindow(1, 1, "Hello World!", NULL, NULL);
    if(!window) {
        //! Error init window
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.f);

    float lastTime = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        ratio = width / (float) height;
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        //* draw objects
        interpolacao();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

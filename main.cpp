#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

using std::cout;

GLFWwindow *createWindow() {
  if (!glfwInit()) {
    cout << "Failed to initialize GLFW\n";
    return NULL;
  }

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
    glfwCreateWindow(1280, 720, "RenderIO", nullptr, nullptr);

  if (!window) {
    cout << "Failed to create window\n";
    return NULL;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGL(glfwGetProcAddress)) {
    cout << "Failed to load GLAD\n";
    return NULL;
  }

  return window;
}

int main() {
  auto *window = createWindow();
  if (window == NULL) 
    return -1;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);


    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
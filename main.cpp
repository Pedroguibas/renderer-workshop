#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

using std::cout;

GLFWwindow *createWindow() {
  if (!glfwInit()) {
    cout << "Falha ao iniciar GLFW\n";
    return NULL;
  }

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
    glfwCreateWindow(1280, 720, "Renderer Workshop", nullptr, nullptr);

  if (!window) {
    cout << "Falha ao criar a janela\n";
    return NULL;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGL(glfwGetProcAddress)) {
    cout << "Falha ao carregar GLAD\n";
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


    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
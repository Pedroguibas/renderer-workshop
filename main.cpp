#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using std::cout;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}


GLFWwindow *createWindow()
{
  if (!glfwInit())
  {
    cout << "Falha ao iniciar GLFW\n";
    return NULL;
  }

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "Renderer Workshop", nullptr, nullptr);

  if (!window)
  {
    cout << "Falha ao criar a janela\n";
    return NULL;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGL(glfwGetProcAddress))
  {
    cout << "Falha ao carregar GLAD\n";
    return NULL;
  }

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  return window;
}

int main()
{
  auto *window = createWindow();
  if (window == NULL)
    return -1;

  // aplica cor de fundo
  glClearColor(0.25, 0.25, 0.3, 1);

  // cria vertices do triângulo
  float vertices[] = {
    //  x        y       z     r     g     b     a
      -0.5f, -0.2887f, -1.5f, 1.0f, 0.0f, 0.0f, 1.0f,
       0.0f,  0.5774f, -1.5f, 0.0f, 1.0f, 0.0f, 1.0f,
       0.5f, -0.2887f, -1.5f, 0.0f, 0.0f, 1.0f, 1.0f
  };

  // cria vértex buffer object
  GLuint VBO;
  glGenBuffers(1, &VBO);

  // cria vertex array object
  GLuint VAO;
  glGenVertexArrays(1, &VAO);

  // binda vertex array e buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindVertexArray(VAO);

  // envia vértices para a GPU
  glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(vertices),
      vertices,
      GL_STATIC_DRAW);

  // explica para a GPU como interpretar os bytes enviados
  glVertexAttribPointer(
      0,                 // localização do parametro
      3,                 // quantidade de valores enviados
      GL_FLOAT,          // tipo dos valores
      GL_FALSE,          // os valores devem ser normalizados?
      7 * sizeof(float), // tamanho de cara conjunto de valores
      (void *)0          // offset de valores
  );
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
    1,
    4,
    GL_FLOAT,
    GL_FALSE,
    7 * sizeof(float),
    (void*)(3*sizeof(float))
  );
  glEnableVertexAttribArray(1);

  
  Shader *shader;
  try {
    shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
  } catch (const std::exception &error) {
    cout << error.what();
    return -1;
  }

  int windowHeight, windowWidth; 
  float rotation = 0;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // limpa o buffer de cores para atualizar a cor do fundo
    glClear(GL_COLOR_BUFFER_BIT);

    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    
    rotation += 0.01f;
    shader->use();
    shader->setMat4("P", glm::perspective(glm::radians(60.0f),(float)windowWidth / (float)windowHeight, 0.1f, 100.0f));
    shader->setMat4("R", glm::rotate(glm::mat4(1.0f), rotation, glm::vec3{0.0f, 0.0f, 1.0f}));
    glDrawArrays(
      GL_TRIANGLES,
      0,
      3
    );
    

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  delete shader;

  return 0;
}
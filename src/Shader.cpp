#include <Shader.h>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  const std::string vertexSrc = Shader::readFile(vertexPath);
  const std::string fragmentSrc = Shader::readFile(fragmentPath);

  GLuint vertexShader = compile(GL_VERTEX_SHADER, vertexSrc.c_str());
  GLuint fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentSrc.c_str());

  m_id = linkProgram(vertexShader, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() {

}


GLuint Shader::compile(const GLenum type, const char *src) {
  const GLuint shader = glCreateShader(type);

  glShaderSource(
    shader,
    1,
    &src,
    nullptr
  );
  glCompileShader(shader);

  GLint success;

  glGetShaderiv(
    shader,
    GL_COMPILE_STATUS,
    &success
  );

  if (!success) { 
    char infoLog[512];
    
    glGetShaderInfoLog(
      shader,
      512,
      nullptr,
      infoLog
    );

    if (type == GL_VERTEX_SHADER) {
      throw std::runtime_error(
        "Falha ao carregar o Vertex Shader:\n"
         + std::string(infoLog)
      );
    } else {
      throw std::runtime_error(
        "Falha ao carregar o Fragment Shader:\n"
        + std::string(infoLog)
      );
    }
  }

  return shader;
}

GLuint Shader::linkProgram(GLuint vertex, GLuint fragment) {
  GLuint program = glCreateProgram();

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {
    char infoLog[512];

    glGetProgramInfoLog(
      program,
      512,
      nullptr,
      infoLog
    );

    throw std::runtime_error(
      "Falha ao linkar o programa do Shader:\n"
      + std::string(infoLog)
    );
  }

  return program;
}

void Shader::use() const {
  glUseProgram(m_id);
}

std::string Shader::readFile(const std::string &path) {
  std::ifstream file(path);

  if (!file.is_open())
    throw std::runtime_error("Falha ao abrir o shader: " + path);

  std::stringstream buffer;

  buffer << file.rdbuf();

  return buffer.str();
}

GLint Shader::getLocation(const std::string &name) noexcept {
  auto it = m_locations.find(name);

  if (it != m_locations.end()) {
    return it->second;
  }

  GLint location = glGetUniformLocation(m_id, name.c_str());

  m_locations[name] = location;

  return location;
}

void Shader::setFloat(const std::string &name, float val) noexcept {
  glUniform1f(getLocation(name), val);
}
void Shader::setInt(const std::string &name, int val) noexcept {
  glUniform1i(getLocation(name), val);
}
void Shader::setBool(const std::string &name, bool val) noexcept {
  glUniform1i(getLocation(name), val);
}
void Shader::setVec2(const std::string &name, float x, float y) noexcept {
  glUniform2f(getLocation(name), x, y);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) noexcept {
  glUniform3f(getLocation(name), x, y, z);
}
void Shader::setVec4(
  const std::string &name, float x, float y, float z, float w
) noexcept {
  glUniform4f(getLocation(name), x, y, z, w);
}
void Shader::setVec2(const std::string &name, glm::vec2 vec) noexcept {
  glUniform2f(getLocation(name), vec.x, vec.y);
}
void Shader::setVec3(const std::string &name, glm::vec3 vec) noexcept {
  glUniform3f(getLocation(name), vec.x, vec.y, vec.z);
}
void Shader::setVec4(const std::string &name, glm::vec4 vec) noexcept {
  glUniform4f(getLocation(name), vec.x, vec.y, vec.z, vec.w);
}
void Shader::setMat4(const std::string &name, glm::mat4 mat) noexcept {
  glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}
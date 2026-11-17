#pragma once

#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader {
  public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator =(const Shader&) = delete;

    void use() const;

    void setFloat(const std::string &name, float val) noexcept;
    void setInt(const std::string &name, int val) noexcept;
    void setBool(const std::string &name, bool val) noexcept;
    void setVec2(const std::string &name, float x, float y) noexcept;
    void setVec3(const std::string &name, float x, float y, float z) noexcept;
    void setVec4(const std::string &name, float x, float y, float z, float w) noexcept;
    void setVec2(const std::string &name, glm::vec2 vec) noexcept;
    void setVec3(const std::string &name, glm::vec3 vec) noexcept;
    void setVec4(const std::string &name, glm::vec4 vec) noexcept;
    void setMat4(const std::string &name, glm::mat4 mat) noexcept;

  private:
    GLuint m_id;
    std::unordered_map<std::string, GLint> m_locations;
    
    GLint getLocation(const std::string &name) noexcept;

    GLuint compile(const GLenum type, const char* src);

    static GLuint linkProgram(GLuint vert, GLuint frag);

    static std::string readFile(const std::string &path);

};
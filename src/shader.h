#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    static std::shared_ptr<Shader> getShader(const std::string& shaderName);

    void use() const;
    void unuse() const;

    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, glm::mat4 value);

private:
    void checkShaderCompileErrors(GLuint shader, const std::string& path);
    void checkProgramLinkErrors(GLuint program);

private:
    GLuint shaderProgram;
    std::unordered_map<std::string, GLint> uniform_locations;

    GLuint compileShader(GLenum type, const std::string& path);

    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};

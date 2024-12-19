#include "shader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

static const std::filesystem::path shaders_dir = "../shaders";

std::unordered_map<std::string, std::shared_ptr<Shader>> Shader::shaders;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexPath.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentPath.c_str());

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    checkProgramLinkErrors(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::use() const {
    glUseProgram(shaderProgram);
}

void Shader::unuse() const {
    glUseProgram(0);
}

GLuint Shader::compileShader(GLenum type, const std::string& path) {
    std::ifstream shaderFile(path);
    if (!shaderFile.is_open()) {
        throw std::runtime_error("ERROR::SHADER::FILE_NOT_FOUND: " + path);
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    std::string shaderCode = shaderStream.str();
    const char* shaderSource = shaderCode.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    checkShaderCompileErrors(shader, path);

    return shader;
}

void Shader::checkShaderCompileErrors(GLuint shader, const std::string& path) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error("ERROR::SHADER::COMPILATION_FAILED (" + path + "): " + std::string(infoLog));
    }
}

void Shader::checkProgramLinkErrors(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error("ERROR::SHADER::PROGRAM_LINKING_FAILED: " + std::string(infoLog));
    }
}

std::shared_ptr<Shader> Shader::getShader(const std::string& shaderName) {

    auto it = shaders.find(shaderName);
    if (it != shaders.end()) {
        return it->second;
    }

    std::filesystem::path vertexShader = (shaders_dir / (shaderName + ".vs"));
    std::filesystem::path fragmentShader = (shaders_dir / (shaderName + ".fs"));

    auto shader = std::make_shared<Shader>(vertexShader, fragmentShader);

    return shaders[shaderName] = shader;
}

void Shader::setUniform(const std::string& name, float value) {
    GLint location = uniform_locations[name];
    if (location == 0) {
        location = glGetUniformLocation(shaderProgram, name.c_str());
        uniform_locations[name] = location;
    }
    glUniform1f(location, value);
}

void Shader::setUniform(const std::string& name, glm::mat4 value) {
    GLint location = uniform_locations[name];
    if (location == 0) {
        location = glGetUniformLocation(shaderProgram, name.c_str());
        uniform_locations[name] = location;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

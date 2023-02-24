#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragementSource;
};

class Shader {
private:
    std::string m_filepath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    // Set Uniforms
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    unsigned int GetUniformLocation(const std::string& name);
};


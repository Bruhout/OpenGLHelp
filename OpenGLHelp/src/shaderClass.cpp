#include "../include/shaderClass.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    FILE* vertexShaderFile = fopen("shaders/vertex.shader" , "r");
    if(vertexShaderFile == NULL)
    {
        std::cout << "error opening vertex shader file\n";
    }
    FILE* fragmentShaderFile = fopen("shaders/fragment.shader" , "r");
    if(fragmentShaderFile == NULL)
    {
        std::cout << "error opening fragment shader file\n";
    }

    char vertexCode[4098];
    int counter = 0;
    char buffer;
    while(fread(&buffer , 1 , 1 , vertexShaderFile)!=0)
    {
        vertexCode[counter] = buffer;
        counter++;
    }
    vertexCode[counter] = '\0';


    char fragmentCode[4098];
    counter=0;
    while(fread(&buffer , 1 , 1 , fragmentShaderFile)!=0)
    {
        fragmentCode[counter] = buffer;
        counter++;
    }
    fragmentCode[counter] = '\0';

    // at this point, the shader code has been read
    const char* vShaderCode = vertexCode;
    const char* fShaderCode = fragmentCode;

    // 2. compile shaders
    GLuint vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    
    // vertexShader Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    // print compile errors if any
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    // print compile errors if any
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::use()
{
    glUseProgram(ID);
}


void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 
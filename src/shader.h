#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

class Shader 
{
private:
    unsigned int ID;
public:
    Shader(const char*vertexPath, const char* fragmentPath)
    {   
        
        printf("Current working dir: %s\n", get_current_dir_name());

        // handle path
        std::string tmpVertPath = "src/";
        tmpVertPath += vertexPath;
        const char* vertPath = tmpVertPath.c_str();
        std::cout << vertPath << std::endl;
        
        std::string tmpFragPath = "src/"; 
        tmpFragPath += fragmentPath;
        const char* fragPath = tmpFragPath.c_str();
        std::cout << fragPath << std::endl;

        // read in vertex shader
        std::string vertexCode;
        std::string line;
        std::ifstream v (vertPath);
        if (!v.is_open())
            std::perror("error while opening file");
        while (std::getline(v, line)) 
            vertexCode = vertexCode + line + "\n";
        if (v.bad())
            perror("error while reading file");
        // read vertex Shader       

        // read in fragment shader
        std::string fragmentCode;
        // std::string line;
        std::ifstream f (fragPath);
        if (!f.is_open())
            std::perror("error while opening file");
        while (std::getline(f, line)) 
            fragmentCode = fragmentCode + line + "\n";
        if (f.bad())
            perror("error while reading file");
        
        const char* vertexShaderSource = vertexCode.c_str();
        const char* fragmentShaderSource = fragmentCode.c_str();
        

        // compile shaders
        
        unsigned int vertex, fragment;
        
	    vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexShaderSource, NULL);
		glCompileShader(vertex);
		checkCompileError(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragment);
        checkCompileError(fragment, "FRAGMENT");

		// link shaders
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
        checkCompileError(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
        
    }
    
    unsigned int getID() 
    {
        return ID;
    }
    void use()
    {
        glUseProgram(ID);
    }

private: 
    void checkCompileError(GLuint shader, std::string type) 
    {
        
		// check shader compile errors
		GLint success;
		GLchar infoLog[1024];
        if(type != "PROGRAM") {
		    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            
		    if (!success) {
			    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		        std::cout << "ERROR::SHADER::COMPILATION_ERROR of type: "
                          << type << "\n" << infoLog << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: "
                    << type << "\n" << infoLog << std::endl;
            }
        }
    }
};
#endif

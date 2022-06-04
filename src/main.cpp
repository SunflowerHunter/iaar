// #define GLFW_INCLUDE_NONE
#include <iostream>
#include <math.h>

#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow *window);
void errorCallback(int error, const char* description);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";


int main() {
				
	if (!glfwInit()) {
	    std::cout << "Failed to initialize GLFW" << std::endl;
	    return -1;
	}
    				
				
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
				
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);
				
	glfwSetErrorCallback(errorCallback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
    
    // build and compile shader program
    Shader coolShades("vertShader.vs", "fragShader.fs");

		
	// vertices
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f, // bottom right
		 0.5f,  0.5f, 0.0f, // top right
		-0.5f,  0.5f, 0.0f  // top left
	};
				
	unsigned int indices[] = {
		0, 1, 2, 
		0, 2, 3
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 
			GL_STATIC_DRAW);
				
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 
            GL_STATIC_DRAW);
    
	// format the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
				
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
			
	//float timeValue = 0;
    
    coolShades.use();

	while (!glfwWindowShouldClose(window)) {

        keyCallback(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
								
		// set uniforms
		// timeValue = glfwGetTime();
		//float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		//int vertexColorLocation = glGetUniformLocation(coolShades.getID(), "ourColor");
		// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);



		// draw triangle
		coolShades.use();
        glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



		/* Swap front and back buffers */
		glfwSwapBuffers(window);
    	/* Poll for and process events */
    	glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
}


void keyCallback(GLFWwindow *window)
{
				if(glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
}

void errorCallback(int error, const char* description) 
{
				fprintf(stderr, "Error %d: %s\n", error, description);
}

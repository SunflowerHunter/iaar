// #define GLFW_INCLUDE_NONE
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
				glfwInit();
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

				GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
				
				if (window == NULL) {
								std::cout << "Failed to create GLFW window" << std::endl;
								glfwTerminate();
								return -1;
				}
				glfwMakeContextCurrent(window);
				//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

				 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
								std::cout << "Failed to initialize GLAD" << std::endl;
								return -1;
				}

				while (!glfwWindowShouldClose(window)) {

								processInput(window);

								glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
								glClear(GL_COLOR_BUFFER_BIT);

								/* Swap front and back buffers */
								glfwSwapBuffers(window);
								
								/* Poll for and process events */
								glfwPollEvents();
				}

				glfwTerminate();
				return 0;
}
/*
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
}
*/

void processInput(GLFWwindow *window)
{
				if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
}


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shaderClass.h"
#include "../include/textureClass.h"

#include <iostream>
#include <math.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//SETTINGS
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
 
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //-=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=-
    //SETUP SHADERS
    const char* vertexShaderSource = "shaders/vertex.shader";
    const char* fragmentShaderSource = "shaders/fragment.shader";

    Shader shaderProgram = Shader(vertexShaderSource , fragmentShaderSource);


    //-=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=-
    //VERTEX DATA
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f   ,   1.0f, 0.0f,   // top right
         0.5f, -0.5f, 0.0f   ,   1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f   ,   0.0f, 1.0f,   // bottom left
        -0.5f,  0.5f, 0.0f   ,   0.0f, 0.0f    // top left 
    };

    int indices[] = {
        0 , 1 , 2 ,
        2 , 3 , 0
    };

    //-=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=-
    // PERFORM TRANSFORMS

    /*
    */
    glm::mat4 transformMat(1.0f);
    transformMat = glm::rotate(transformMat , 1.5f , glm::vec3(0.0f , 0.0f , 1.0f));
    transformMat = glm::scale(transformMat , glm::vec3(0.5f , 0.5f , 0.5f));


    unsigned int transformMatLoc = glGetUniformLocation(shaderProgram.ID , "transform");
    glUniformMatrix4fv(
        transformMatLoc , 1 , GL_FALSE , glm::value_ptr(transformMat)
    );

    //-=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=-
    //SEND VERTEX DATA TO GPU

    GLuint vertexBuffer;
    GLuint vertexArray;
    GLuint elementBuffer;
    glGenBuffers(1 , &vertexBuffer);
    glGenVertexArrays(1 , &vertexArray);
    glGenBuffers(1 , &elementBuffer);

    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER , vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);

    // POSITION DATA
    glVertexAttribPointer(
        0/*index*/, 3 /*per vert*/ ,
        GL_FLOAT /*type*/, GL_FALSE /*normalize*/,
        5 * sizeof(float) /*stride*/, (void*)0 /*offset*/
    );
    glEnableVertexAttribArray(0);

    // TEXTURE COORDINATE DATA  
    glVertexAttribPointer(
        1 , 2 ,
        GL_FLOAT , GL_FALSE ,
        5 * sizeof(float) , (void*)(3*sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram.ID);
    glBindVertexArray(vertexArray);

    //-=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=-

    //INITIALIZE THE TEXTURE
    Texture containerImage = Texture("container.jpg");


    //-=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=--=-=-=-=-=-=--=-=-=-
    //RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram.ID);
        // glDrawArrays(GL_TRIANGLES , 0 , 3);
        glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        // glFlush();
    }
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


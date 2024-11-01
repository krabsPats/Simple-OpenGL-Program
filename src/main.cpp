#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void init(){
    glfwInit();
    //triple hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* windowLoad(){
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello world", NULL, NULL);
    glfwMakeContextCurrent(window);


    return window;
} 


void frameDynamic(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);  

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

main(){

    const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


    init();

    GLFWwindow* window = windowLoad();

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Error GLAD";
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glfwSetFramebufferSizeCallback(window, frameDynamic);  
        
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    

    glfwTerminate();
    return 0;
}

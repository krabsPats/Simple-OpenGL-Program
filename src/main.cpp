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

void gladSec(){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Error GLAD";
    }

    glViewport(0,0,800,600);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
}

void frameSize(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);  

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

main(){

    init();

    GLFWwindow* window = windowLoad();
    
    gladSec();

    glfwSetFramebufferSizeCallback(window, frameSize);  
        
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

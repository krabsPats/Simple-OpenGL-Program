#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
        std::cout << "resizing";
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window); 
    }  


main(){

    glfwInit();
    //triple hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  


    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello world", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Error GLAD";
    }

    glViewport(0,0,800,600);



    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}

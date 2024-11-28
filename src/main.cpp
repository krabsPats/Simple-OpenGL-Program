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

float verticesData[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

    init();

    GLFWwindow* window = windowLoad();

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Error GLAD";
        return -1;
    }

    glClearColor(0.5f, 1.0f, 0.3f, 1.0f);

    glfwSetFramebufferSizeCallback(window, frameDynamic);  




    unsigned int vertexSource = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexSource, 1, &vertexShaderSource, NULL);

    glCompileShader(vertexSource);

    unsigned int fragmentSource = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentSource, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentSource);

    unsigned int shaderProgram =  glCreateProgram();

    glAttachShader(shaderProgram, vertexSource);
    glAttachShader(shaderProgram, fragmentSource);

    glLinkProgram(shaderProgram);

    unsigned int VBO;
    unsigned int VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    //Make buffer.

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Bind a target to our buffer which is necessery for the gpu to know what is this buffer about.

    glBufferData(GL_ARRAY_BUFFER,sizeof(verticesData), verticesData, GL_STATIC_DRAW);
    //Here we add the data that we need for the graphcis pipeline. 
    //Vertex Shader -> Geometry Shader -> Shape assembly and so on...
    
    //GL_STATIC_DRAW is set once with a piece of data (in these case the vertex array) where is used many times for gpu.
    //GL_DYNAMAIC_DRAW is different in where it set mutiple times in runtime and it also used many times for the gpu.


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,  3 * sizeof(float), (void*) 0);

    //ARG/Parameter: 1. vertex layout pos in vertex shader. 
    //2. the amount of pos in the vertex like for exampe 0,0,0.
    //3. the vertices data type. There is argument where it is also due to the vec in the vertex shader.
    //4. to normalize or not. Normalizing is when putting a number in a float range like 255 to 0.0 - 1.0.
    //5. the offset location.

    glEnableVertexAttribArray(0);

        
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);   



        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();    


        

    }

    glfwTerminate();
    return 0;
}
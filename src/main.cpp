#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct drawData{
    unsigned int shaderProgramStruct;
    unsigned int VAOSTRUCT1;
    unsigned int VAOSTRUCT2;

};



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
    
    drawData* data = (drawData*)glfwGetWindowUserPointer(window);
    unsigned int shaderProgram = data->shaderProgramStruct;
    unsigned int VAO1 = data->VAOSTRUCT1;
    unsigned int VAO2 = data->VAOSTRUCT2;
    

    glViewport(0,0,width,height);  

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

     glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(window);
}


int main(){

    std::cout << "hello";

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


    if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Error GLAD";
        return -1;
    }

    glClearColor(0.1f, 0.8f, 0.8f, 1.0f);

    glfwSetFramebufferSizeCallback(window, frameDynamic);  


    float verticesData[] = {
        0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };  
    float verticesData2[] = {
        -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };  



    unsigned int vertexSource = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexSource, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexSource);
    //Creates a shader which compile a certain GLSL code. This is required to the graphic pipeline.

    unsigned int fragmentSource = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentSource, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentSource);
    //Creare a shader which compile a certain GLSL code. This is required to the graphic pipeline.

    unsigned int shaderProgram =  glCreateProgram();
    glAttachShader(shaderProgram, vertexSource);
    glAttachShader(shaderProgram, fragmentSource);
    glLinkProgram(shaderProgram);

    unsigned int VBO[2];

    unsigned int VAO[2];


    glGenBuffers(2, VBO);

    glGenVertexArrays(2, VAO);
    //Make buffers.

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
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


    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

    glBufferData(GL_ARRAY_BUFFER,sizeof(verticesData2), verticesData2, GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0);

    glEnableVertexAttribArray(0);
   

    drawData data;

    data.shaderProgramStruct = shaderProgram;
    data.VAOSTRUCT1 = VAO[0];
    data.VAOSTRUCT2 = VAO[1];

    glfwSetWindowUserPointer(window, &data);


    while(!glfwWindowShouldClose(window))
    { 
        glClear(GL_COLOR_BUFFER_BIT);   



        glUseProgram(shaderProgram);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();    


        

    }

    glfwTerminate();
    return 0;
}
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <unistd.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "learnopengl/shader_m.h"
#include "learnopengl/camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void drawJariRoda(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint offset);
void drawCircleFill(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides,GLfloat color);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 3.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

unsigned int VBO, VAO, VBO_1, VAO_1, VBO_2, VAO_2, VBO_3, VAO_3, VBO_4, VAO_4;

int main()
{
    camera.ProcessKeyboard(FORWARD, 1.01);
    camera.ProcessMouseMovement(-900, 1000);
    camera.ProcessKeyboard(FORWARD, 0.1);
    camera.ProcessMouseMovement(0, -700);
    camera.ProcessKeyboard(BACKWARD, 0.07);


    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("7.4.camera.vs", "7.4.camera.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // x (horizontal) y (vertikal) z (dalam)
        // belakang
        -1.5f,   -0.5f,  -0.5f,   0.0f,   0.0f, //1
        -0.25f, -0.5f,  -0.5f,   1.0f,   0.0f, //2
        -0.25f,  0.5f,  -0.5f,   1.0f,   1.0f, //3
        -0.25f,  0.5f,  -0.5f,   1.0f,   1.0f, //4
        -1.5f,    0.f,   -0.5f,   0.0f,   1.0f, //5
        -1.5f,   -0.5f,  -0.5f,   0.0f,   0.0f, //6

        -0.25f, -0.5f,  -0.5f,   0.0f,   0.0f,
         1.25f, -0.5f,  -0.5f,   1.0f,   0.0f,
         1.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
         1.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
        -0.25f,  0.5f,  -0.5f,   0.0f,   1.0f,
        -0.25f, -0.5f,  -0.5f,   0.0f,   0.0f,

         1.25f, -0.5f, -0.5f,    0.0f,   0.0f,
         2.f, -0.5f,  -0.5f,   1.0f,   0.0f,
         2.f,  0.f,  -0.5f,   1.0f,   1.0f,
         1.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
         1.25f,  -0.5f,  -0.5f,   0.0f,   1.0f,
         2.f, 0.f,  -0.5f,   0.0f,   0.0f,

        

        // // // depan
        -1.5f,   -0.5f,  0.5f,   0.0f,   0.0f, //1
        -0.25f, -0.5f,  0.5f,   1.0f,   0.0f, //2
        -0.25f,  0.5f,  0.5f,   1.0f,   1.0f, //3
        -0.25f,  0.5f,  0.5f,   1.0f,   1.0f, //4
        -1.5f,    0.f,  0.5f,   0.0f,   1.0f, //5
        -1.5f,   -0.5f, 0.5f,   0.0f,   0.0f, //6

        -0.25f, -0.5f,  0.5f,   0.0f,   0.0f,
         1.25f, -0.5f,  0.5f,   1.0f,   0.0f,
         1.25f,  0.5f,  0.5f,   1.0f,   1.0f,
         1.25f,  0.5f,  0.5f,   1.0f,   1.0f,
        -0.25f,  0.5f,  0.5f,   0.0f,   1.0f,
        -0.25f, -0.5f,  0.5f,   0.0f,   0.0f,

         1.25f, -0.5f, 0.5f,    0.0f,   0.0f,
         2.f, -0.5f,  0.5f,   1.0f,   0.0f,
         2.f,  0.f,  0.5f,   1.0f,   1.0f,
         1.25f,  0.5f, 0.5f,   1.0f,   1.0f,
         1.25f,  -0.5f, 0.5f,   0.0f,   1.0f,
         2.f, 0.f, 0.5f,   0.0f,   0.0f,

        // // kiri
        -1.5f,  0.f,     0.5f,   1.0f,   0.0f,
        -1.5f,  0.f,    -0.5f,   1.0f,   1.0f,
        -1.5f, -0.5f,   -0.5f,   0.0f,   1.0f,
        -1.5f, -0.5f,   -0.5f,   0.0f,   1.0f,
        -1.5f, -0.5f,    0.5f,   0.0f,   0.0f,
        -1.5f,  0.f,     0.5f,   1.0f,   0.0f,

        // // kanan        
         2.f,  0.f,   0.5f,   1.0f,   0.0f,
         2.f,  0.f,  -0.5f,   1.0f,   1.0f,
         2.f, -0.5f,  -0.5f,   0.0f,   1.0f,
         2.f, -0.5f,  -0.5f,   0.0f,   1.0f,
         2.f, -0.5f,   0.5f,   0.0f,   0.0f,
         2.f,  0.f,   0.5f,   1.0f,   0.0f,

         1.6f,  0.25f,   0.5f,   1.0f,   0.0f,
         1.6f,  0.25f,  -0.5f,   1.0f,   1.0f,
         2.f,  0.f,  -0.5f,   0.0f,   1.0f,
         2.f,  0.f,  -0.5f,   0.0f,   1.0f,
         2.f,  0.f,   0.5f,   0.0f,   0.0f,
         1.6f,  0.25f,   0.5f,   1.0f,   0.0f,

        //  // atas
        -0.25f,  0.5f,   0.5f,   0.0f,   0.0f,
         1.25f,  0.5f,   0.5f,   1.0f,   0.0f,
         1.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
         1.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
        -0.25f,  0.5f,  -0.5f,   0.0f,   1.0f,
        -0.25f,  0.5f,   0.5f,   0.0f,   0.0f,

        //  // bawah
        -1.5f,   -0.5f,  -0.5f,   0.0f,   1.0f,
         2.f, -0.5f,  -0.5f,   1.0f,   1.0f,
         2.f, -0.5f,   0.5f,   1.0f,   0.0f,
         2.f, -0.5f,   0.5f,   1.0f,   0.0f,
        -1.5f,   -0.5f,   0.5f,   0.0f,   0.0f,
        -1.5f,   -0.5f,  -0.5f,   0.0f,   1.0f,


        //penutup kaca
        -1.5f,    0.f,    0.5f,   0.0f,   0.0f,
        -1.f,  0.2f,   0.5f,   1.0f,   0.0f,
        -1.f,  0.2f,  -0.5f,   1.0f,   1.0f,
        -1.f,  0.2f,  -0.5f,   1.0f,   1.0f,
        -1.5f,    0.f,   -0.5f,   0.0f,   1.0f,
        -1.5f,    0.f,    0.5f,   0.0f,   0.0f, 
    };

    float kaca[] = {
        // kaca
        -1.f,    0.2f,    0.5f,   0.0f,   0.0f,
        -0.25f,  0.5f,   0.5f,   1.0f,   0.0f,
        -0.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
        -0.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
        -1.f,    0.2f,   -0.5f,   0.0f,   1.0f,
        -1.f,    0.2f,    0.5f,   0.0f,   0.0f, 


        1.25f,  0.5f,   0.5f,   1.0f,   0.0f,
         1.25f,  0.5f,  -0.5f,   1.0f,   1.0f,
         1.6f,  0.25f,  -0.5f,   0.0f,   1.0f,
         1.6f,  0.25f,  -0.5f,   0.0f,   1.0f,
         1.6f,  0.25f,   0.5f,   0.0f,   0.0f,
         1.25f,  0.5f,   0.5f,   1.0f,   0.0f,

         //kaca samping kanan
         0.3f,    0.f,    -0.52f,   0.0f,   0.0f,
        0.3f,  0.4f,   -0.52f,   1.0f,   0.0f,
        -0.17f,  0.4f,  -0.52f,   1.0f,   1.0f,
        -0.17f,  0.4f,  -0.52f,   1.0f,   1.0f,
        0.3f,   0.f,   -0.52f,   0.0f,   1.0f,
        -1.02f,    0.f,    -0.52f,   0.0f,   0.0f, 

         0.5f,    0.f,    -0.52f,   0.0f,   0.0f,
        0.5f,  0.4f,   -0.52f,   1.0f,   0.0f,
        1.1f,  0.4f,  -0.52f,   1.0f,   1.0f,
        1.1f,  0.4f,  -0.52f,   1.0f,   1.0f,
        0.5f,   0.f,   -0.52f,   0.0f,   1.0f,
        1.1f,    0.f,    -0.52f,   0.0f,   0.0f, 


        //kaca samping kiri
         0.3f,    0.f,    0.52f,   0.0f,   0.0f,
        0.3f,  0.4f,   0.52f,   1.0f,   0.0f,
        -0.17f,  0.4f,  0.52f,   1.0f,   1.0f,
        -0.17f,  0.4f,  0.52f,   1.0f,   1.0f,
        0.3f,   0.f,   0.52f,   0.0f,   1.0f,
        -1.02f,    0.f,    0.52f,   0.0f,   0.0f, 

        0.5f,    0.f,    0.52f,   0.0f,   0.0f,
        0.5f,  0.4f,   0.52f,   1.0f,   0.0f,
        1.1f,  0.4f,  0.52f,   1.0f,   1.0f,
        1.1f,  0.4f,  0.52f,   1.0f,   1.0f,
        0.5f,   0.f,   0.52f,   0.0f,   1.0f,
        1.1f,    0.f,    0.52f,   0.0f,   0.0f, 
    };

   

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    ////

    

    ////

   

    ////

    glGenVertexArrays(1, &VAO_4);
    glGenBuffers(1, &VBO_4);

    glBindVertexArray(VAO_4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kaca), kaca, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2, texture3, texture4;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("resources/textures/red.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //

    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("resources/textures/glass.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    ourShader.setInt("texture3", 2);
    ourShader.setInt("texture4", 3);

    // render loop
    // -----------
    int offset = 0;
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // bind textures on corresponding texture units
        // glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // glActiveTexture(GL_TEXTURE0);

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 100);
        }


        glBindVertexArray(VAO_4);
        glBindTexture(GL_TEXTURE_2D, texture2);
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 100);
        }


        int k,l;

        glGenVertexArrays(1, &VAO_1);
        glGenBuffers(1, &VBO_1);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO_1);
        
        // glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);  
        // glActiveTexture(GL_TEXTURE1);

        ourShader.use();
        for(k=0;k<5;k++){
            //drawCircleFill(0.375f, -0.375f, 0.6f-k*0.001f, 0.6f, 60,1);
            for(l=0;l<20;l++){
                drawJariRoda(1.1f, -0.5f, 0.51f+k*0.001f, 0.35f+l*0.001, 360, offset);
                drawJariRoda(-0.5f, -0.5f, (0.51f+k*0.001f), 0.35f+l*0.001, 360, offset);
                drawJariRoda(1.1f, -0.5f, -1*(0.51f+k*0.001f), 0.35f+l*0.001, 360, offset);
                drawJariRoda(-0.5f, -0.5f, -1*(0.51f+k*0.001f), 0.35f+l*0.001, 360, offset);
            }
            
        }
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        offset = (offset + 5) % 360;
         //usleep(1000);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void drawJariRoda(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint offset) {
    GLint numRadius = 10;
    GLint numberOfVertices = numberOfSides + numRadius;
    GLfloat doublePi = 3.0f * M_PI; 
    GLfloat circleVerticesX[numberOfVertices]; 
    GLfloat circleVerticesY[numberOfVertices]; 
    GLfloat circleVerticesZ[numberOfVertices];

    

    int k = 0;

    for(int i = 0; i < numberOfVertices; i++) {
        circleVerticesX[i] = x + (radius * cos(offset +(i-k) * doublePi / numberOfSides));
        circleVerticesY[i] = y + (radius * sin(offset +(i-k) * doublePi / numberOfSides));
        circleVerticesZ[i] = z;


        if ( (i-k) % (numberOfVertices/ numRadius) == 0) {
            k++;
            i++;
            circleVerticesX[i] = x;
            circleVerticesY[i] = y;
            circleVerticesZ[i] = z;
        }
    }

    GLfloat allCircleVertices[numberOfVertices*5];
    for (int i = 0; i < numberOfVertices; i++) {
        allCircleVertices[i*5] = circleVerticesX[i];
        allCircleVertices[i*5 +1] = circleVerticesY[i];
        allCircleVertices[i*5 +2] = circleVerticesZ[i];
        allCircleVertices[i*5 +3] = 0;
        allCircleVertices[i*5 +4] = 1;
    }

                                                     

    glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(allCircleVertices), allCircleVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_LINE_LOOP, 0, numberOfVertices);
}

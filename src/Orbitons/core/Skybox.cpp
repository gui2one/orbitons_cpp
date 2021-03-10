#include "Skybox.h"

Skybox::Skybox(){

}

void Skybox::init(){
    

    // init shader

    m_shader.loadVertexShaderSource("../../resources/shaders/skybox_shader.vert");
    m_shader.loadFragmentShaderSource("../../resources/shaders/skybox_shader.frag");

    m_shader.createShader();
    //init openGL stuff
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);




    std::vector<std::string> paths = {
        "../../resources/textures/skybox/right.jpg",
        "../../resources/textures/skybox/left.jpg",
        "../../resources/textures/skybox/top.jpg",
        "../../resources/textures/skybox/bottom.jpg",
        "../../resources/textures/skybox/front.jpg",
        "../../resources/textures/skybox/back.jpg"
    };

    for(size_t i=0; i < paths.size(); i++){
        int width, height, nrChannels;
        unsigned char * data;
        stbi_set_flip_vertically_on_load(0);    
        data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);

        if(data){

            // printf("texture width : %d\n", width);
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);

        }else{
            std::cout << "Cubemap tex failed to load at path: " << paths[i] << std::endl;
            stbi_image_free(data);
        }
    }


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  


    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    m_vbo = 0;
    glCreateBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(float), skyboxVertices,GL_STATIC_DRAW);

    m_vao = 0;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void Skybox::draw(Camera* camera){
    glDepthMask(GL_FALSE);


    glm::mat4 view = glm::mat4(1.0f);
    glm::vec3 up_vector(0.f,1.f,0.f);
    view *= glm::lookAt(
        camera->position,
        camera->target_position,
        glm::normalize(up_vector)
    );

    // remove position from matrix
    view = glm::mat4(glm::mat3(view)); 

    m_shader.useProgram();
    glUniformMatrix4fv(glGetUniformLocation(m_shader.m_id, "u_projection"), 1, GL_FALSE, glm::value_ptr(camera->projection));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.m_id, "u_view"), 1, GL_FALSE, glm::value_ptr(view));
        
    // ... set view and projection matrix

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


}
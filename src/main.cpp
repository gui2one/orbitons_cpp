
// #define GLEW_DLL

#include "pch.h"
// #include "core.h"

#include "orbital_body.h"


#include "core/MeshUtils.h"
#include "core/Material.h"
#include "core/Object3d.h"
#include "core/Timer.h"
#include "core/Camera.h"
#include "core/ObjectLoader.h"

using  Orbitons::OrbitalBody;

int curMaterialID = 0;
std::vector<std::shared_ptr<Material>> materials;
std::vector<std::shared_ptr<Object3d>> objects;

void create_materials(){

    std::shared_ptr<PhongMaterial> phong_material = std::make_shared<PhongMaterial>();
    std::shared_ptr<UnlitMaterial> unlit_material = std::make_shared<UnlitMaterial>();
    phong_material->diffuseColor = glm::vec3(1.0f, 0.1f, 0.1f);
    unlit_material->color = glm::vec3(0.f, 0.5f, 0.f);
    
    materials.push_back(phong_material);
    materials.push_back(unlit_material);
}

void cycle_materials(){
    if(curMaterialID >= materials.size() -1){
        curMaterialID = 0;
    }else{
        curMaterialID ++;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // printf("Key -> %d\n", key);
    // printf("Scancode -> %d\n", scancode);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {

    }else if( scancode == 39 /* m key */&& action == GLFW_PRESS){
        cycle_materials();
    }
}

int main(){

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(500, 500, "Orbitons -- Renderer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);


    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if( !status){
        printf("Problem with glad\n");
        return -1;
    }



    printf("GL version: %s\n", glGetString(GL_VERSION));
    printf("GL shading language version: %s\n", 
    glGetString(GL_SHADING_LANGUAGE_VERSION));
    glfwSwapInterval(1);

    // unlit_material->initShader();
    create_materials();
    Timer timer;
    ObjLoader loader;
    Camera camera(glm::radians(60.0f),1.0f);
    camera.position.y = 3.0f;
    camera.target_position.y = 1.0f;
    glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);

    Mesh mesh;

    mesh = loader.assimp_load("resources/objects/dragon.glb");
    // mesh = MeshUtils::makeGrid(4.0f,4.0f, 3, 3);

    MeshUtils::rotateX(mesh, -PI*0.5);
    MeshUtils::computeNormals(mesh);





    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint ibo = 0;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), mesh.indices.data(), GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0); // position --> 0 offset
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void *)(3* sizeof(float))); // normal --> 3 offset


    glEnable(GL_DEPTH_TEST);
    
    float angle = 0.0f;

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        timer.update();


        glm::mat4 view = glm::mat4(1.0f);

        float radius = 5.0f;
        float speed = 0.3f;
        angle += timer.getDeltaTime() * speed;
        //camera.position.x = sinf(angle) * radius;
        //camera.position.z = cosf(angle) * radius;
        view *= glm::lookAt(
            camera.position,
            camera.target_position,
            glm::normalize(up_vector)
        );

        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, angle, up_vector);

        glm::vec3 lightPos = glm::vec3(0.f, 2.f, 0.f);
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // material.initShader();

        // printf("%d\n", curMaterialID);

        materials[curMaterialID]->useProgram();

        std::shared_ptr<Material> curMat = materials[curMaterialID];


        glUniform3fv(glGetUniformLocation(curMat->getShader()->m_id,"u_lightPos"), 1 , glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(curMat->getShader()->m_id,"u_cameraPos"), 1 , glm::value_ptr(camera.position));

        glUniformMatrix4fv(glGetUniformLocation(curMat->getShader()->m_id,"u_model"), 1, GL_FALSE,glm::value_ptr(model));
        
        glUniformMatrix4fv(glGetUniformLocation(curMat->getShader()->m_id, "u_projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
        glUniformMatrix4fv(glGetUniformLocation(curMat->getShader()->m_id, "u_view"), 1, GL_FALSE, glm::value_ptr(view));
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        //glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
        // update other events like input handling 
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwTerminate();


    return 0;
}
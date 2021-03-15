#include "Orbitons.h"
#include "core.h"
using namespace Orbitons;

Application app;




void createObjects(){
    ObjLoader loader;
    Ref<Object3d> dragon;
    Ref<Object3d> plane;
    
    
    dragon = MakeRef<Object3d>();
    dragon->m_mesh = loader.assimp_load(ORBITONS_RES_DIR"/objects/dragon_full.glb");
    dragon->buildBuffers();
    dragon->setScale(glm::vec3(10.f));
    dragon->setPosition(glm::vec3(0.f, 0.0f, 0.f));

    std::static_pointer_cast<PhongMaterial>(dragon->m_material)->setDiffuseColor(glm::vec3(1.f));

    app.m_scene.add(dragon);


    plane = MakeRef<Object3d>();
    plane->m_mesh = MeshUtils::makeGrid(1.f, 1.f, 2, 2);
    MeshUtils::rotateX(plane->m_mesh, PI / 2.0f);
    MeshUtils::computeNormals(plane->m_mesh);
    plane->buildBuffers();
    plane->setScale(glm::vec3(1.0f));

    app.m_scene.add(plane);
}

int main(int argc, char** argv){

    createObjects();


    app.run();

    printf("Termination .....\n");
    exit(EXIT_SUCCESS);
    return 0;
}
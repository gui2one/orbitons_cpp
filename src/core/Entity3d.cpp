#include "Entity3d.h"

Entity3d::Entity3d():
    position(glm::vec3(0., 0.f, 0.f)), 
    rotation(glm::vec3(0., 0.f, 0.f)), 
    scale(glm::vec3(1., 1.f, 1.f)){

}

void Entity3d::applyTransforms(){
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::scale(matrix, scale);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));

    transforms = matrix;
}

void Entity3d::setScale(glm::vec3 _scale){
    scale = _scale;
    applyTransforms();
}
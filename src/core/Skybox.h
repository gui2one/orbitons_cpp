#ifndef SKYBOX_H
#define SKYBOX_H

#include "../pch.h"
#include "Shader.h"
#include "Camera.h"

#include "../opengl_debug.h"
class Skybox{
public:
    Skybox();

    void init();
    void draw(Camera* camera);
    GLuint m_id;
    GLuint m_vao;
    GLuint m_vbo;

    Shader m_shader;

private:

};
#endif /* SKYBOX_H */
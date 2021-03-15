#ifndef OPENGL_SKYBOX_H
#define OPENGL_SKYBOX_H

#include "core.h"
#include "pch.h"
#include "Renderer/Shader.h"
#include "Renderer/Skybox.h"
#include "Core/Camera.h"

class OpenGLSkybox : public Skybox{
public:
    virtual ~OpenGLSkybox(){};


    virtual void init() override ;
    virtual void draw(Camera* camera) override;
    uint32_t m_id;
    uint32_t m_vao;
    uint32_t m_vbo;

    std::shared_ptr<Shader> m_shader;

private:

};
#endif /* OPENGL_SKYBOX_H */
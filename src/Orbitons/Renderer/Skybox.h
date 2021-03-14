#ifndef SKYBOX_H
#define SKYBOX_H

#include "core.h"
#include "pch.h"
#include "Shader.h"
#include "Core/Camera.h"

class Skybox{
public:
    virtual ~Skybox() = default;

    static Orbitons::Ref<Skybox> create();

    virtual void init() = 0;
    virtual void draw(Camera* camera) = 0;

private:

};
#endif /* SKYBOX_H */
#ifndef MATERIAL_H
#define MATERIAL_H

#include "../pch.h"
#include "../core.h"
#include "glm/vec3.hpp"
#include "Shader.h"

class Material
{



public:
    Orbitons::Ref<Shader> m_shader;
    std::string m_type_name;

    Material(){
        printf("Material Constructor\n");

    }


    virtual void setUniforms() = 0;
    virtual void initShader() = 0;

    inline void useProgram(){
        setUniforms();
        m_shader->useProgram();
    }
    inline Orbitons::Ref<Shader> getShader(){
        return m_shader;
    }
    inline std::string getTypeName(){
        return m_type_name;
    }
    
};

class PhongMaterial : public Material
{

private:

public:

    glm::vec3 diffuseColor; 
    glm::vec3 specularColor; 
    PhongMaterial(){
        m_type_name = "Phong";
        diffuseColor = glm::vec3(1.f, 0.2f, 1.f);
        specularColor = glm::vec3(1.f, 1.f, 1.f);

        initShader();
    }

    inline void setUniforms() override {

        glUniform3fv(glGetUniformLocation(m_shader->m_id, "material.diffuseColor"), 1 , glm::value_ptr(diffuseColor));
        glUniform3fv(glGetUniformLocation(m_shader->m_id, "material.specularColor"), 1 , glm::value_ptr(specularColor));
    }

    inline void initShader() override {
        m_shader = std::make_shared<Shader>();
        m_shader->loadVertexShaderSource("../../resources/shaders/phong_shader.vert");
        m_shader->loadFragmentShaderSource("../../resources/shaders/phong_shader.frag");
        m_shader->createShader();
    }
};

class UnlitMaterial : public Material
{

public:

    glm::vec3 color;

    UnlitMaterial(){
        m_type_name = "Unlit";
        color = glm::vec3(0.2f,0.5f, 0.2f);
        initShader();
    }
    inline void initShader() override{
        m_shader = std::make_shared<Shader>();
        m_shader->loadVertexShaderSource("../../resources/shaders/unlit_shader.vert");
        m_shader->loadFragmentShaderSource("../../resources/shaders/unlit_shader.frag");
        m_shader->createShader();
    }

    inline void setUniforms() override {
        
        glUniform3fv(glGetUniformLocation(m_shader->m_id, "material.color"), 1 , glm::value_ptr(color));
    }

};


#endif /* MATERIAL_H */
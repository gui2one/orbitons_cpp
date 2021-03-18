#ifndef MATERIAL_H
#define MATERIAL_H

#include "core.h"
#include "pch.h"
#include "glm/vec3.hpp"
#include "Shader.h"
#include <glad/glad.h>

namespace Orbitons
{

    class Material
    {
    public:
        Ref<Shader> m_shader;
        std::string m_type_name;

        virtual ~Material(){};

        static Ref<Material> create();
        virtual void setUniforms() = 0;
        virtual void initShader() = 0;
        virtual void setDiffuseColor(glm::vec3 color){};

        inline void useProgram()
        {
            setUniforms();
            m_shader->useProgram();
        }
        inline Ref<Shader> getShader()
        {
            return m_shader;
        }
        inline GLuint getShaderID()
        {
            return m_shader->getID();
        }
        inline std::string getTypeName()
        {
            return m_type_name;
        }

        friend void setDiffuseColor(glm::vec4 color);
    };

    class PhongMaterial : public Material
    {

    private:
    public:
        glm::vec3 diffuseColor;
        glm::vec3 specularColor;
        PhongMaterial()
        {
            m_type_name = "Phong";
            diffuseColor = glm::vec3(0.9f, 0.1f, 0.1f);
            specularColor = glm::vec3(1.f, 1.f, 1.f);

            initShader();
        }

        inline void setUniforms() override
        {

            glUniform3fv(glGetUniformLocation(m_shader->getID(), "material.diffuseColor"), 1, glm::value_ptr(diffuseColor));
            glUniform3fv(glGetUniformLocation(m_shader->getID(), "material.specularColor"), 1, glm::value_ptr(specularColor));
        }

        inline void initShader() override
        {
            m_shader = Shader::create();
            m_shader->loadVertexShaderSource(ORBITONS_RES_DIR "/shaders/phong_shader.vert");
            m_shader->loadFragmentShaderSource(ORBITONS_RES_DIR "/shaders/phong_shader.frag");
            m_shader->createShader();
        }

        virtual void setDiffuseColor(glm::vec3 color) override
        {
            diffuseColor = color;
            setUniforms();
        }
    };

    class UnlitMaterial : public Material
    {

    public:
        glm::vec3 color;

        UnlitMaterial()
        {
            m_type_name = "Unlit";
            color = glm::vec3(0.2f, 0.5f, 0.2f);
            initShader();
        }
        inline void initShader() override
        {
            m_shader = Shader::create();
            m_shader->loadVertexShaderSource(ORBITONS_RES_DIR "/shaders/unlit_shader.vert");
            m_shader->loadFragmentShaderSource(ORBITONS_RES_DIR "/shaders/unlit_shader.frag");
            m_shader->createShader();
        }

        inline void setUniforms() override
        {

            glUniform3fv(glGetUniformLocation(m_shader->getID(), "material.color"), 1, glm::value_ptr(color));
        }
    };

}

#endif /* MATERIAL_H */
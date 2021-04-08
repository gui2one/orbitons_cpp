#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H
#include <pch.h>
#include <core.h>

#include "Renderer/Shader.h"
#include <fstream>

static std::string loadShaderFile(std::string path)
{

	std::ifstream input(path);
	std::string output = "";
	for (std::string line; std::getline(input, line);)
	{

		output += line;
		output += "\n";
	}

	return output;
}

namespace Orbitons
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		virtual ~OpenGLShader(){};
		virtual void loadVertexShaderSource(std::string filePath) override;
		virtual void loadFragmentShaderSource(std::string filePath) override;

		virtual unsigned int compileShader(unsigned int type, const std::string &source) override;
		virtual unsigned int createShader() override;
		virtual unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) override;
		virtual std::string getVertexShaderSource() override;
		virtual std::string getFragmentShaderSource() override;
		virtual uint32_t getID() override { return m_id; }
		virtual void useProgram() override;

		virtual void uploadUniform3fv(glm::vec3 clr, const char *location_name = "") override
		{
			glUniform3fv(glGetUniformLocation(getID(), location_name), 1, glm::value_ptr(clr));
		};

	public:
		uint32_t m_id;

	private:
		std::string vertexShaderSource;
		std::string fragmentShaderSource;
		/* add your private declarations */
	};
}

#endif /* OPENGL_SHADER_H */
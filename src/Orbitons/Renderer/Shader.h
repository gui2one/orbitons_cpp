#ifndef SHADER_H
#define SHADER_H
#include "pch.h"

#include <fstream>
namespace Orbitons
{
	class Shader
	{
	public:
		virtual ~Shader(){};

		static std::shared_ptr<Shader> create();

		virtual void loadVertexShaderSource(std::string filePath) = 0;
		virtual void loadFragmentShaderSource(std::string filePath) = 0;

		virtual unsigned int compileShader(unsigned int type, const std::string &source) = 0;
		virtual unsigned int createShader() = 0;
		virtual unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) = 0;
		virtual std::string getVertexShaderSource() = 0;
		virtual std::string getFragmentShaderSource() = 0;

		virtual uint32_t getID() = 0;
		virtual void useProgram() = 0;

		virtual void uploadUniform3fv(glm::vec3 clr, const char *location_name = "") = 0;

	private:
		// std::string vertexShaderSource;
		// std::string fragmentShaderSource;
		// uint32_t m_id;
	};
} // namespace Orbitons

#endif /* SHADER_H */
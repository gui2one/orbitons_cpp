#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "core.h"
#include "pch.h"
#include "Renderer/Texture.h"
namespace Orbitons
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture();

		virtual ~OpenGLTexture();
		virtual void load(std::string path) override;
		virtual void setData(int width, int height, unsigned char *buffer) override;

		virtual unsigned int getID() override { return id; };
		virtual int getWidth() override { return width; };
		virtual int getHeight() override { return height; };
		virtual int getBPP() override { return bpp; };
		virtual void bind(unsigned int slot) override;
		virtual void unbind(unsigned int slot) override;

	private:
		unsigned int id;
		int width, height, bpp;
	};
} // namespace Orbitons

#endif /* OPENGL_TEXTURE_H */

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "pch.h"
#include "core.h"
#include "Renderer/Texture.h"

class OpenGLTexture : public Texture
{
	public:
		
		OpenGLTexture();
		
		virtual ~OpenGLTexture();
		virtual void load(std::string path) override;
		virtual void setData(int width, int height, unsigned char* buffer) override;

		virtual unsigned int getID() override { return id; };
		virtual int getWidth() override { return width; };
		virtual int getHeight() override { return height; };
		virtual int getBPP() override { return bpp; };
		virtual void bind() override;
		virtual void unbind() override;
		
	private:
		unsigned int id;
		int width, height, bpp;	
	
};

#endif /* OPENGL_TEXTURE_H */ 

#ifndef TEXTURE_H
#define TEXTURE_H

#include "pch.h"
#include "core.h"

class Texture
{
	public:
		
		static Orbitons::Ref<Texture> create();
		
		virtual ~Texture(){};
		virtual void load(std::string path) = 0;
		virtual void setData(int width, int height, unsigned char* buffer) = 0;

		virtual unsigned int getID() = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual int getBPP() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		
	private:

};

#endif /* TEXTURE_H */ 
